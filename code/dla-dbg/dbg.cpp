#include "op.h"
#include "opcode.h"

#include "core/behavior.h"
#include "core/timing.h"

#include "cli/code.h"

namespace
{

struct Memory final
{
  std::unique_ptr<Segment> _const_segment;
  std::vector<std::unique_ptr<Segment>> _host_segments;
  std::unique_ptr<Segment> _dla_segment;
  std::unique_ptr<Segment> _dsp_segment;
};

} // namespace

namespace
{

// Behavior Modeling Context
struct BMContext final : public BM::Context
{
  const Instr *_ins = nullptr;
  std::set<Slot> _occupied;

  const Instr *ins(void) const final { return _ins; }
  bool ready(const std::set<Slot> &ss) const final
  {
    for (auto slot : ss)
    {
      if (_occupied.find(slot) != _occupied.end())
      {
        return false;
      }
    }
    return true;
  }

  bool _wfe = false;
  bool _enque = false;
  std::unique_ptr<Transaction> _txn = nullptr;

  void wait(void) final
  {
    _wfe = true;
  }

  void enqueue(std::unique_ptr<Transaction> &&txn) final
  {
    _enque = true;
    _txn = std::move(txn);
  }
};

// Timing Modeling Context
struct TMContext final : public TM::Context
{
public:
  TMContext(const Instr *ins) : _ins{ins}
  {
    // DO NOTHING
  }

public:
  const Instr *ins(void) const final { return _ins; }

private:
  const Instr *_ins = nullptr;
};

// Transaction Context
struct TXNContext final : public Transaction::Context
{
  Memory *_memory = nullptr;

  std::vector<uint8_t> dla_read(uint32_t base, uint32_t size) const final
  {
    std::vector<uint8_t> res;

    auto span = _memory->_dla_segment->read(base, size);

    for (uint32_t n = 0; n < span.size(); ++n)
    {
      res.emplace_back(span.at(n));
    }
      
    return res;
  }

  void dla_write(uint32_t base, const std::vector<uint8_t> &data) final
  {
    _memory->_dla_segment->write(base, data);
  }

#if 0
  uint32_t dla_protect_set(uint32_t base, uint32_t size) final
  {
    throw std::runtime_error{"Not implemented yet"};
  }

  void dla_protect_unset(uint32_t no) final
  {
    throw std::runtime_error{"Not implemented yet"};
  }
#endif
};

} // namespace

namespace
{

struct Event
{
  enum Cat // Category
  {
    Issue,
    Commit,
  };

  Cat cat;

  union Payload
  {
    Transaction *txn;
  };

  Payload payload;
};

Event make_issue_event(void)
{
  Event s;

  s.cat = Event::Cat::Issue;
  // NOTE 'Issue' event has no payload

  return s;
}

Event make_commit_event(Transaction *txn)
{
  Event s;

  s.cat = Event::Cat::Commit;
  s.payload.txn = txn;

  return s;
}

class EventTimeline final
{
public:
  struct EventWithTime
  {
    uint32_t time; // Time offset
    Event event; // Event
  };

public:
  bool empty(void) const { return _content.empty(); }

public:
  void insert(uint32_t time, const Event &evt)
  {
    _content.insert(std::make_pair(time, evt));
  }

  EventWithTime draw(void)
  {
    EventWithTime res;

    res.time = _content.begin()->first;
    res.event = _content.begin()->second;

    _content.erase(_content.begin());

    return res;
  }

private:
  std::multimap<uint32_t, Event> _content;
};

} // namespace

#include <cassert>
#include <iostream>
#include <iomanip>

struct SessionArgs
{
  const Program *program;
  const SystemBM *bm;
  const SystemTM *tm;
};

// TODO Introduce "Observer"
//
// Session may have at most one observer
// - Observer SHOULD outlive Session.
//
// Attributes
// - State
// - Event Timeline
//
// - Memory
// - Program Counter
//
// - Performance Counters (e.g. Elpased Time)
//
// Methods
// - step
// - eval
//
// The design of "Session" looks similar to that of Green Thread.
class Session final
{
public:
  // State describes the state of Control Unit (C/U).
  enum class State
  {
    // C/U is idle (initial state)
    Idle,

    // C/U is busy
    Busy,
    // C/U is idle, but it tries to decode the next instruction for each transcation commit
    WaitingForEvent,
    // C/U is idle and waits for pending transaction commit.
    WaitingForTermination,

    // Final State
    Terminated,

    // Something wrong
    Stuck,
  };

public:
  // TODO Introduce SessionArgs or SessionOptions class
  Session(const SessionArgs *args)
  {
    _program = args->program;
    _bm = args->bm;
    _tm = args->tm;

    // TODO Create Const Host Segment
    // TODO Create Non-Const Host Segments
    // Create DLA Segment
    _memory._dla_segment = std::make_unique<Segment>(_program->dla_segment_size);
    // TODO Attach UnalginedAccessMonitor
    // TODO Create DSP Segment

    // Initialize Timeline
    _timeline.insert(0, make_issue_event());
  }

public:
  ~Session()
  {
    // "fini" call is allowed in any state

    // Reset the states
    // - Clear "Event Stream"
    // - Clear "Pending Transaction"
    // - Reset "Program Counter"
  }

private:
  // Program of interest
  const Program *_program = nullptr;
  const SystemBM *_bm = nullptr;
  const SystemTM *_tm = nullptr;

private:
  State _state = State::Idle;

  void update_state_(const State &s)
  {
    if (_state != s)
    {
      // TODO Notify State Change
      //
      // State Change : Before -> After
      _state = s;
    }
  }

public:
  Memory _memory;

private:
  // bool check_timeline()
  // {
  //    for (auto it = _timeline.begin(); it != _timeline.end(); ++it)
  //    {
  //      if (it->first < _elpased)
  //      {
  //        return false;
  //      }
  //    }
  //    return true;
  // }
  //
  // check_timeline() SHOULD return true before and after "step" call
  //
  // TODO It seems that there is at most ONE FETCH_INSTR command in ccs. Prove this!
  EventTimeline _timeline;

private:
  TXNContext create_txn_ctx_(void)
  {
    TXNContext res;
    {
      res._memory = &_memory;
    }
    return res;
  }

  BMContext create_bm_ctx_(const Instr *ins)
  {
    BMContext ctx;

    ctx._ins = ins;
    ctx._occupied = occupied_slots_();

    return ctx;
  };

  TMContext create_tm_ctx_(const Instr *ins)
  {
    return TMContext{ins};
  }

private: // Manage Transactions
  // TODO Store a pair of TXN and TXNContext
  std::set<std::unique_ptr<Transaction>> _pending_txns;

  std::set<Slot> occupied_slots_(void) const
  {
    std::set<Slot> res;
    for (const auto &txn : _pending_txns)
    {
      res.insert(txn->slot());
    }
    return res;
  }

  Transaction *begin_txn_(std::unique_ptr<Transaction> &&txn)
  {
    // Create a context
    auto txn_ctx = create_txn_ctx_();

    // Begin transcation
    txn->begin(&txn_ctx);

    // Add to pending transaction set
    auto p = txn.get();
    _pending_txns.emplace(std::move(txn));

    return p;
  }

  void commit_txn_(Transaction *txn)
  {
    // Create a context
    auto txn_ctx = create_txn_ctx_();

    // Commit trasncation
    txn->commit(&txn_ctx);

    // Remove from pending transaction set
    for (auto it = _pending_txns.begin(); it != _pending_txns.end(); ++it)
    {
      if (it->get() == txn)
      {
        _pending_txns.erase(it);
        break;
      }
    }
  }

private: // Manage Instruction Register
  bool has_next_instr_(void) const { return _pc < _program->_code.size(); }
  const Instr *next_instr_(void) { return _program->_code.at(_pc); }

private: // Manage Program Counter
  uint32_t _pc = 0; // Program Counter

  uint32_t program_counter_(void) const { return _pc; }
  void increment_program_counter_(void) { _pc += 1; }

private: // Handle Event
  void handle_issue_event_(uint32_t cur_ts)
  {
    if (not has_next_instr_())
    {
      // TODO Use Logging Framework
      // TODO Notify Observer
      std::cout << "Issue failed (nothing to fetch) @ " << cur_ts << std::endl;
      update_state_(State::WaitingForTermination);
      return;
    }

    auto ins = next_instr_();

    // Model Instruction Behavior via B/M
    auto bm_ctx = create_bm_ctx_(ins);
    _bm->model(&bm_ctx);

    if (bm_ctx._wfe)
    {
      std::cout << "Instr " << program_counter_() << " waits for events @ " << cur_ts << std::endl;
      // NOTE "Program Counter" does not change in this case
      update_state_(State::WaitingForEvent);
      return;
    }

    if (bm_ctx._enque)
    {
      auto txn = begin_txn_(std::move(bm_ctx._txn));

      // TODO Notify Observer
      // TODO Use Logger
      std::cout << "Instr " << program_counter_() << " issues transcation " << txn << " @ " << cur_ts << std::endl;
      std::cout << "Begin transaction " << txn << " @ " << cur_ts << std::endl;

      // Query Follow-up EventTiming 
      auto tm_ctx = create_tm_ctx_(ins);
      auto evt_offset = _tm->model(&tm_ctx);

      // Update Timeline
      auto issue_ts = cur_ts + evt_offset.issue_after;
      auto commit_ts = cur_ts = evt_offset.commit_after;

      _timeline.insert(issue_ts, make_issue_event());
      _timeline.insert(commit_ts, make_commit_event(txn));

      // Update Internal States
      increment_program_counter_();
      update_state_(State::Busy);

      // Done!
      return;
    }

    update_state_(State::Stuck);
  }

  void handle_commit_event_(uint32_t cur_ts, Transaction *txn)
  {
    // assert(_state is Busy or WaitingForEvent or WaitingForTermination)

    commit_txn_(txn);

    if (_state == State::WaitingForEvent)
    {
      // CP waits for slot state updates
      _timeline.insert(cur_ts, make_issue_event());
    }

    // TODO Notify Observer
    // TODO Use Logginga Framework
    std::cout << "Transcation " << txn << ": Committed @ " << cur_ts << std::endl;
  }

public: // Performance Counters
  uint32_t _elapsed = 0; // Elapsed Cycle
  // Q. Record step count?
  // Q. How to record Read/Write?
  //    - Segment Observer?
  //      - Segment Observer only checks the activity from one end.
  //      - Let's consider ADLA_LOAD instruction
  //      - This instruction will access Host Segment on "begin" call, and dla_segment on "end" call
  //    - Need a way to record these metrics directly from Transaction
  //      - Via TXNContext(?)
public:
  // "step" processes one Event in Timeline.
  // - "step" may update "Timeline"
  // - "step" may update "State"
  void step(void)
  {
    if (_timeline.empty())
    {
      // TODO Use Logging Framework
      // TODO Notify Observer
      std::cout << "Terminate execution (no reamining event in timeline)" << std::endl;

      update_state_(State::Terminated);
      return;
    }

    // TODO Ensure monotonic increase
    auto ewt = _timeline.draw();

    auto ts = _elapsed = ewt.time;
    auto evt = ewt.event;

    // Invoke Event Handler
    switch (evt.cat)
    {
    case Event::Cat::Issue:
      return handle_issue_event_(ts);
    case Event::Cat::Commit:
      return handle_commit_event_(ts, evt.payload.txn);
    default:
      break;
    }

    // TODO Adjust memory bandwidth and compute commit time
    // - EventTimeline SHOULD be extended to support event cancellation.
    update_state_(State::Stuck);
  }

public:
  void eval(void)
  {
    while (true)
    {
      switch (_state)
      {
      case State::Idle:
      case State::Busy:
      case State::WaitingForEvent:
      case State::WaitingForTermination:
        step();
        break;
      case State::Terminated:
        return;
      case State::Stuck:
        throw std::runtime_error{"Something wrong"};
      default:
        throw std::runtime_error{"Invalid state"};
      }
    }
  }
};

class DBGContext final
{
public:
  DBGContext(Session *s) : _sess{s}
  {
    // DO NOTHING
  }

public:
  Session *sess(void) const { return _sess; }

private:
  Session *_sess = nullptr;
};

struct DBGCommand
{
  virtual ~DBGCommand() = default;

  virtual void run(DBGContext *) const = 0;
};

struct EvalCommand final : public DBGCommand
{
  void run(DBGContext *ctx) const final
  {
    ctx->sess()->eval();
    std::cout << "Execution takes " << ctx->sess()->_elapsed << " cycle" << std::endl;
  }
};

struct DumpCommand final : public DBGCommand
{
  void run(DBGContext *ctx) const final
  {
    auto span = ctx->sess()->_memory._dla_segment->data();

    for (uint32_t row = 0; row < 128 / 16; ++row)
    {
      for (uint32_t col = 0; col < 16; ++col)
      {
        std::cout << "0x";
        std::cout << std::hex << std::setfill('0') << std::setw(2);
        std::cout << span.at(row * 16 + col) + 0;
        std::cout << " ";
      }
      std::cout << std::endl;
    }
  }
};

namespace
{

// issue_latency (default: X)
// execute_latency (default: Y)
//
// Givan "issue_latency" A and "execute_latency" B,
//
// NaiveSystemTM returns fecth_after as A + B, and commit_after as A + B.
// OptimizedSystemTM returns issue_after as A, and commit_after as A + B

struct HardcodedSystemTM final : public SystemTM // As Fallback
{
  EventOffset model(Context *) const final
  {
    EventOffset res;

    res.issue_after = 10;
    res.commit_after = 20;

    return res;
  }
};

} // namespace

// core/
//   include/
//     op.lst
//     memory.h (segment, ...)
//     instr.h
//     timing.h
//     behavior.h
//   src/
//     memory/
//       Segment Observers...
//     op/
//       <PREFIX>.h
//       <PREFIX>.cpp (Decoder / Behavior & Time Model)
// cli/
//   src/
//    session.h
//    session.cpp
//    step.cpp <- STEP
//    eval.cpp <- EVAL
//    dbg.cpp <- MAIN

// Where to put Session?

// OP(OPCODE, PREFIX)

// The current design requires the following actions in order to add a new instruction
// 1. Extend "op.lst"
// 2. Create a corresponding instruction class that implement "Instr" interface
// 3. Extend "Frontend"
//   - "Frontend" is responsible for constructing a sequence of Instr objects from a raw byte stream
//   - Need to design
// 4. Extend "Behavior Model"
//   - Derive "Transcation" class
//   - Register "Decode Logic"
// 5. Extend "Timing Model"
int main(int argc, char **argv)
{
  // Create a program
  Program p;
  {
    // Read ".header" and construct the program
    p.const_segment_size = 0;
    p.host_segment_sizes.emplace_back(1024);
    p.dla_segment_size = 512 * 1024;

    // TODO Fill "Input/Output" to "Segment" mapping
    // - Input Index -> Segment Index
    // - Output Index -> Segment Index

    // Read ".code" and update the program
    // byte *cur = beg;
    //
    // while (cur < end)
    // {
    //   auto decoder = r->lookup(bytes[off]);
    //
    //   if (decoder == nullptr) { throw DecodeFailure; }
    //
    //   auto len = decoder->size();
    //   assert(cur + len <= end);
    //
    //   auto ins = decoder->decode(cur, cur + len);
    //
    //   sess->instrs()->append(std::move(ins));
    //
    //   cur += len;
    // }

    // Add code
    p._code.append(std::make_unique<Relu>());
    p._code.append(std::make_unique<Relu>());

    // TODO Read ".data" and update "data" field
  }

  // Create Behavior/Timing Models
  DefaultSystemBM bm;
  HardcodedSystemTM tm;

  // Create Session Args
  SessionArgs sess_args;

  sess_args.program = &p;
  sess_args.bm = &bm;
  sess_args.tm = &tm;

  // Create a session
  Session sess{&sess_args};

  // Create a debugging context
  DBGContext dbg_ctx{&sess};

  // Parse script and run commands
  {
    EvalCommand eval_cmd;
    eval_cmd.run(&dbg_ctx);

    DumpCommand dump_cmd;
    dump_cmd.run(&dbg_ctx);
  }

  return 0;
}
