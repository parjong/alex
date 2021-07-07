#ifndef CFG_H__
#define CFG_H__

#include <map>
#include <vector>

#include <llvm/IR/BasicBlock.h>

class Block;
class State;
class Graph;

class Block
{
  public:
    Block(llvm::BasicBlock *block);
    ~Block();

  //
  private:
    llvm::BasicBlock *block_;
  public:
    llvm::BasicBlock *block(void) const;

  //
  private:
    std::vector<State *> prev_;
  public:
    const std::vector<State *> &prev(void) const;
  public:
    void addPrev(State *);

  //  
  private:
    std::vector<State *> succ_;
  public:
    const std::vector<State *> &succ(void) const;    
  public:
    void addFollower(State *state);
};

class State
{
  public:
    State();
    ~State();

  //
  private:
    Block *next_;
  public:
    Block *next(void) const;
  public:
    bool forward(Block *blk);

};

class Graph
{
  public:
    Graph();
    ~Graph();
    
  private:
    State *entry_;   
  public:
    State *entry(void) const;

  private:
    std::map<llvm::BasicBlock *, Block *> map_;
  public:
    Block *getBlock(llvm::BasicBlock *B);

  //
  private:
    std::vector<Block *> blocks_;
  private:
    Block *makeBlock(llvm::BasicBlock *block);
    void freeBlocks(void);
  public:
    const std::vector<Block *> &blocks(void) const;
  
  //
  private:
    std::vector<State *> states_;
  public:
    State *makeState(void);
  private:
    void freeStates(void);
  public:
    const std::vector<State *> &states(void) const;
};

Graph *createFromFunction(llvm::Function *F);

#endif
