#include "CFG.h"

#include <assert.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>

#include <set>
#include <queue>

/**
 * Block
 */
Block::Block(llvm::BasicBlock *block) : block_(block)
{
  // Do NOTHING
}

Block::~Block()
{
  // Do NOTHING
}

llvm::BasicBlock *Block::block(void) const
{
  return block_;
}

const std::vector<State *> &Block::prev(void) const
{
  return prev_;
}

const std::vector<State *> &Block::succ(void) const
{
  return succ_;
}

void Block::addFollower(State *state)
{
  succ_.push_back(state);
}

/**
 * State
 */
State::State() : next_(nullptr)
{
  // Do NOTHING
}

State::~State()
{
  // Do NOTHING
}

Block *State::next(void) const
{
  return next_;
}

bool State::forward(Block *blk) 
{
  if ( next_ != nullptr )
  {
    return false;
  }

  next_ = blk;
  return true;
}

/**
 * GRAPH
 */
Graph::Graph() : entry_(nullptr)
{
  entry_ = makeState();
}

Graph::~Graph()
{
  freeBlocks();
  freeStates();
}

State *Graph::entry(void) const
{
  return entry_;
}

Block *Graph::getBlock(llvm::BasicBlock *B)
{
  auto it = map_.find(B);

  if ( it == map_.end() )
  {
    return map_[B] = makeBlock(B);
  }

  return it->second;
}

Block *Graph::makeBlock(llvm::BasicBlock *block)
{
  Block *obj = new Block(block);
  blocks_.push_back(obj);
  return obj;
}
 
void Graph::freeBlocks(void)
{
  for (auto block : blocks_)
    delete block;
}

const std::vector<Block *> &Graph::blocks(void) const
{ 
  return blocks_; 
}

State *Graph::makeState(void)
{
  State *obj = new State();

  states_.push_back(obj);

  return obj;      
}

void Graph::freeStates(void)
{
  for (auto state : states_)
    delete state;
}

const std::vector<State *> &Graph::states(void) const
{ 
  return states_; 
}

// std::pair<State *, llvm::BasicBlock *>?
class Candidate
{
  public:
    Candidate(State *state, llvm::BasicBlock *B)
      : state_(state), B_(B)
    {
    }
  public:
    ~Candidate()
    {
    }
  private:
    State *state_;
    llvm::BasicBlock *B_; 
  public:
    State *state(void) { return state_; }
    llvm::BasicBlock *block(void) { return B_; }
};

Graph *createFromFunction(llvm::Function *func)
{
  Graph *res = new Graph();

  //
  std::set<llvm::BasicBlock *> visited;
  std::queue<Candidate *> candidates;

  //
  {
    llvm::BasicBlock *BB = &func->getEntryBlock();
    candidates.push(new Candidate(res->entry(), BB));
  }

  //
  while ( !candidates.empty() )
  {
    std::unique_ptr<Candidate> curr( candidates.front() );
  
    Block *block = res->getBlock(curr->block());
    
    //
    curr->state()->forward(block);
  
    //
    if ( visited.count(curr->block()) == 0 )       
    {
      llvm::TerminatorInst *I = curr->block()->getTerminator();

      for (unsigned i = 0; i < I->getNumSuccessors(); ++i)
      {
        llvm::BasicBlock *BB = I->getSuccessor(i);        

        State *n_state = res->makeState();

        block->addFollower(n_state);

        candidates.push(new Candidate(n_state, BB));
      }
    }

    //
    visited.insert(curr->block());   
    candidates.pop();
  }
  
  return res;
}

