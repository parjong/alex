#ifndef __TIMING_MODEL_H__
#define __TIMING_MODEL_H__

struct EventOffset
{
  uint32_t issue_after = 0;
  uint32_t commit_after = 0;
};

// Timing Model (TM)
struct TM
{
  struct Context
  {
    virtual ~Context() = default;

    virtual const Instr *ins(void) const = 0;
  };

  virtual ~TM() = default;

  virtual EventOffset model(Context *) const = 0;
};

// System-level Timing Model
struct SystemTM : public TM
{
  virtual ~SystemTM() = default;
};

#endif // __TIMING_MODEL_H__
