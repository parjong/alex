#include "emit/emit.h"
#include "emit/code.h"

#include <assert.h>

#include "CFG.h"
#include "build/FrontendActionRunner.h"

#include <llvm/Analysis/Interval.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/BasicBlock.h>

#include <clang/Frontend/FrontendActions.h>

#include <getopt.h>

#include <string>
#include <vector>

#include <map>
#include <unordered_map>

#include <set>
#include <queue>

#include <iostream>

// [min, max]
class Interval
{
  public:
    Interval()  { }
    ~Interval() { }
  private:
    int min_;
    int max_;
};

namespace Analyzer
{  
  // A unit of read/write 
  class Region
  {
    public:
      Region()  { }
      ~Region() { }
  };

  // A set of regions
  class RegionSet : public std::set<Region *>
  {
    public:
      RegionSet()   { }
      ~RegionSet()  { }
    public:
      bool add(Region *R)
      {
        if ( this->find(R) == this->end() )
        {
          return false;
        }

        this->insert(R);
        return true;
      }
  };
 
  class Memory
  {
    public:
      Memory()   { }
      ~Memory()  { }
    private:
      std::map<const llvm::Value *, Region *> mRegion;
    public:
      Region *create(const llvm::Value *V);
      Region *lookup(const llvm::Value *V) const;
    public:      
      Region *expand(const llvm::Value *V)
      {
        Region *R = this->lookup(V);

        if ( R == nullptr )        
          return this->create(V);        

        return R;
      }
  };
  
  class Heap
  {
    public:
      Heap()  { }
      ~Heap() { }

    private:
      std::map<const Region *, Interval *> state_;

    public:
      Interval *create(const Region *R);
      Interval *lookup(const Region *R) const;
      bool update(const Region *R, Interval *);           
  };
  
  class PointerContext
  {
    public:
      PointerContext()  { }
      ~PointerContext() { }

    private:
      std::map<const llvm::Value *, RegionSet *> ctxt_;

    public:
      RegionSet *create(const llvm::Value *V)
      {
        assert( ctxt_.find(V) == ctxt_.end() );

        return ctxt_[V] = new RegionSet();
      }
    public:
      RegionSet *lookup(const llvm::Value *V) const
      {
        auto it = ctxt_.find(V);

        if ( it == ctxt_.end() )
        {
          return nullptr;
        }

        return it->second;        
      }
    public:
      RegionSet *exapnd(const llvm::Value *V, Region *R)
      {
        RegionSet *RS = this->lookup(V);

        if ( RS == nullptr )
        {
          RS = this->create(V);
        }

        return RS;
      }
  };

  class ValueContext
  {
    public:
      ValueContext()  { } 
      ~ValueContext() { }
    private:
      std::map<const llvm::Value *, Interval *> ctxt_;
    public:
      Interval *lookup(const llvm::Value *V) const
      {
        auto it = ctxt_.find(V);

        if ( it == ctxt_.end() )
        {
          return nullptr;
        }

        return it->second;
      }
  };

  class TransferFn
  {
    public:
      TransferFn()  { }
      ~TransferFn() { }

    private:
      // Flow-insensitive
      bool update(const llvm::AllocaInst *AI, Memory& M, Heap& H, PointerContext& PC)
      {
        bool ret = false;

        // Create a region (if necessary)
        Region *R = M.expand(AI);

        // Update 'Heap'
        if ( H.lookup(R) == nullptr )
        {
          H.create(R);
          ret = true;
        }
        
        // Update 'PointerContext'
        RegionSet *RS = PC.lookup(AI);

        if ( RS == nullptr )
        {
          RS  = PC.create(AI);
          ret = true;
        }

        return RS->add(R);
      }
    private:
      // Flow-sensitive
      bool update(const llvm::StoreInst *SI, Memory& M, Heap& H, const PointerContext& PC, const ValueContext& PreVC, ValueContext& PostVC)
      {
        // store i32 %len, i32* %len.addr, align 4
        const llvm::Value *lhs = SI->getValueOperand();
        const llvm::Value *rhs = SI->getPointerOperand();

        bool ret = false;

        RegionSet *RS = PC.lookup(rhs);

        if ( RS == nullptr )
        {
          return false; //
        }

        Interval *I = PreVC.lookup(lhs);

        if( I == nullptr )
        {
          return false;
        }

        for (const Region *R : *RS)
        {
          // For each region in RS
          if ( H.update(R, I) )
          {
            ret = true;
          }
        }

        return ret;
      }
  };
}

#ifdef AAA
// Var |-> Interval
class Domain
{
  public:
    Domain(Symbols& symb) : symb_(symb)  { }
    ~Domain() { }

  private:
    std::vector<Interval *> values_;

  public:
    void join(const Domain& D)
    {
      return;
    }
  private:
    void update(const llvm::Instruction *I, const Domain& src)
    {   
      std::cout << "======================================" << std::endl;
      I->dump();
      std::cout << I->getName().str() << std::endl;
      std::cout << I->getOpcodeName() << std::endl;
      I->getDebugLoc().dump();

      if (const llvm::AllocaInst *AI = llvm::dyn_cast<llvm::AllocaInst>(I))
      {
        update(AI, src);
      }
      else if (const llvm::StoreInst *SI = llvm::dyn_cast<llvm::StoreInst>(I))
      {
        update(SI, src);
      }
      std::cout << "======================================" << std::endl;
    }
  public:
    bool update(const Block *blk, const Domain& src)
    {
      std::cout << __FILE__ << ":" << __LINE__ << std::endl;

      llvm::BasicBlock *B = blk->block();

      for (auto I = B->begin(); I != B->end(); ++I)
      {
        update(I, src);
      }

      return false;
    }
};

/**
 *
 */
class FunctionContext
{
  public:
    FunctionContext() { }
    ~FunctionContext() { }
  private:
    Symbols symb_;
    std::map<State *, Domain *> cached_;
  public:
    Domain *domain(State *state)
    {
      auto it = cached_.find(state);

      if ( it == cached_.end() )
      {
        return cached_[state] = new Domain(symb_);
      }

      return it->second;
    }
};

void analyze(const Graph& G)
{
  assert( G.entry() != nullptr );
  assert( G.entry()->next() != nullptr );

  FunctionContext ctxt;

  std::queue<Block *> q;

  // Insert the entry state into the walklist
  q.push( G.entry()->next() );

  while ( !q.empty() )
  {    
    Block *block = q.front();
   
    // 1. Join all the states
    Domain d_join;

    for (State *s_prev : block->prev())
    {
      Domain *d_prev = ctxt.domain(s_prev);

      d_join.join(*d_prev);
    }

    // 2. Propagates the updated states into the successors
    for (State *s_next : block->succ())
    {
      std::cout << __FILE__ << ":" << __LINE__ << std::endl;
      Domain *d_next = ctxt.domain(s_next);

      assert( d_next != nullptr );

      if ( !d_next->update(block, d_join) )
      {
        continue;
      }

      if ( s_next->next() == nullptr )
      {
        continue;
      }

      q.push( s_next->next() );
    }

    q.pop();
  }
}
#endif 

void run(Emit& emit)
{
  auto vec = emit.enumerate<Code>();

  std::cout << "len(vec) = " << vec.size() << std::endl;

  hiberlite::bean_ptr<Code> code = vec[0];
  {
    FrontendActionRunner actionRunner;

    clang::EmitLLVMOnlyAction bcGenAction;

    actionRunner.append(bcGenAction);

    actionRunner.run(code->content(), "sample.cc");    

    std::unique_ptr<llvm::Module> M( bcGenAction.takeModule() );  

    M->dump();
//
//    for (auto F = M->begin(); F != M->end(); ++F) 
//    { 
//      std::unique_ptr<Graph> g( createFromFunction(F) );
//      analyze(*g);
//    }   
  }
}

/**
 * Usage: <tool> --db <db>
 */
int main(int argc, char * const argv[], char * const envp[])
{ 
  std::string *output_val = nullptr;  
 
  static struct option long_opts[] =
  {
    { "db",  required_argument,  0,  'd' },
    { 0,     0,                  0,  0   },
  };

  while ( 1 )
  {
    int opt = getopt_long(argc, argv, "d:", long_opts, NULL);

    if ( opt == -1 ) break;

    switch ( opt )
    {
      case 'd':
        assert( optarg != nullptr );
        assert( output_val == nullptr );

        output_val = new std::string(optarg);

        break;
      default:
        break;
    }
  }

  if ( output_val == nullptr )
  {
    std::cerr << "ERROR: --db should be specified" << std::endl;
    exit(EXIT_FAILURE);
  }

  Emit emit( *output_val );

  run(emit);

  return 0;
}
