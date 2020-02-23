#ifndef __BEHAVIOR_H__
#define __BEHAVIOR_H__

#include "slot.h"
#include "instr.h"
#include "transaction.h"

#include <map>
#include <memory>
#include <set>

// Behavior Modeling
struct BM
{
  // TODO Add error handlers
  struct Context
  {
    virtual ~Context() = default;

    // >>> INPUIT <<<
    // ins() returns the instruction of interest
    virtual const Instr *ins(void) const = 0;

    // TODO Pass H/W parameters

    // ready(ss) returns true if all the slots specified by "ss" are ready.
    virtual bool ready(const std::set<Slot> &ss) const = 0;

    // >>> OUTPUT <<<
    virtual void wait() = 0;
    virtual void enqueue(std::unique_ptr<Transaction> &&) = 0;
  };

  virtual ~BM() = default;

  virtual void model(Context *) const = 0;
};

// Instruction-level Behavior Modeling
template <Opcode Code> struct InstrBM : public BM
{
  virtual ~InstrBM() = default;

  Opcode opcode(void) const { return Code; }
};

// System-level Behavior Modeling
struct SystemBM : public BM
{
  virtual ~SystemBM() = default;
};

// Built-in System-level Behavior Modeling
class DefaultSystemBM final : public SystemBM
{
public:
  struct Registry final
  {
  private:
    std::map<Opcode, const BM *> _content;

  public:
    // TODO Return nullptr if there is no behavior modeling
    const BM *lookup(const Opcode &op) const
    {
      return _content.at(op);
    }

    void insert(const Opcode &op, const BM *bm)
    {
      _content[op] = bm;
    }

  public:
    static Registry *get(void)
    {
      static Registry r;
      return &r;
    }
  };

public:
  // Self-reigistration helper
  template <typename T> struct ExtendWith : public T
  {
    ExtendWith(Registry *r = Registry::get())
    {
      r->insert(T::opcode(), this);
    }
  };

public:
  DefaultSystemBM(const Registry *r = Registry::get()) : _registry{r}
  {
    // DO NOTHING
  }

public:
  void model(Context *ctx) const final
  {
    _registry->lookup(ctx->ins()->opcode())->model(ctx);
  }

private:
  const Registry *_registry = nullptr;
};

#endif // __BEHAVIOR_H__
