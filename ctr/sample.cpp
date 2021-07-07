// ctrd - A framework for Contract Description
//
// HOW TO USE
//
// ```
// using ...::me;
//
// UNLESS(cond).FIX(me);
// ```
//
// ```
// UNLESS(cond).FIX(caller);
// ```
//
// (TO BE ADDED)
//
// UNLESS(cond).FIX("..."); // FIX SUBCOMPONENT
#include <memory>

#include <cassert>
#include <iostream>

//
// FRAMEWORK CODE
//
namespace ctr
{

class Handler;

struct Frame // Nested Frame
{
private:
  std::shared_ptr<Frame> const _parent;
  const Handler * const _handler = nullptr;

public:
  Frame(const std::shared_ptr<Frame> &p, const Handler *h) : _parent{p}, _handler{h}
  {
    // DO NOTHING
  }

public:
  const std::shared_ptr<Frame> &parent(void) const { return _parent; }
  const Handler *handler(void) const { return _handler; }
};

struct ThreadContext // Thread-local Context
{
public:
  friend class Tracker;
  friend class Handler;

private: // Only Tracker and Handler are allowed to access this field
  std::shared_ptr<Frame> top;

private:
  static ThreadContext &get(void)
  {
    thread_local ThreadContext ctx;
    return ctx;
  }
};

class Handler
{
public:
  struct FaultByMe final
  {
  };

  struct FaultByCaller final
  {
  };

private:
  std::shared_ptr<Frame> _frame;

public:
  Handler()
  {
    _frame = std::make_shared<Frame>(ThreadContext::get().top, this);
    ThreadContext::get().top = _frame;
  }

public:
  virtual ~Handler()
  {
    assert(ThreadContext::get().top == _frame);
    ThreadContext::get().top = _frame->parent();
  }

public:
  enum class PostAction
  {
    Stop,
    Go,
  };

  virtual PostAction handle(const FaultByMe &) const { return PostAction::Go; }
  virtual PostAction handle(const FaultByCaller &) const { return PostAction::Go; }
};

struct Me // Phantom Type
{
};

Me me;

struct Caller // Phantom Type
{
};

Caller caller;

class Tracker // TODO Keep __FILE__ and __LINE__
{
private:
  template <typename Callable> void visit_frame_with_(Callable &&f) const
  {
    auto frame = ThreadContext::get().top;

    for (auto frame = ThreadContext::get().top; frame != nullptr; frame = frame->parent())
    {
      switch (f(frame->handler()))
      {
      case Handler::PostAction::Stop:
        return;
      case Handler::PostAction::Go:
      default:
        break;
      }
    }

    assert(false);
  }

public:
  void FIX(const Me &) const
  {
    Handler::FaultByMe fault;
    visit_frame_with_([&fault] (const Handler *h) { return h->handle(fault); });
  }

  void FIX(const Caller &) const
  {
    Handler::FaultByCaller fault;
    visit_frame_with_([&fault] (const Handler *h) { return h->handle(fault); });
  }
};

Tracker make_tracker(void) { return Tracker{}; }

} // namespace ctr

#define UNLESS(cond) if (not (cond)) ::ctr::make_tracker()

//
// USER CODE
//
using ctr::me;
using ctr::caller;

struct MyHandler final : public ctr::Handler
{
  // Override this method to handle "my fault"
  PostAction handle(const FaultByMe &) const final
  {
    std::cerr << "My Fault" << std::endl;
    return PostAction::Stop;
  }

  PostAction handle(const FaultByCaller &) const final
  {
    std::cerr << "Caller's Fault" << std::endl;
    throw std::runtime_error{"caller's fault!"};
  }
};

int main(int argc, char **argv)
{
  int x = 4;

  {
    MyHandler h;

    std::cout << __LINE__ << std::endl;
    UNLESS(x == 3).FIX(me);
    std::cout << __LINE__ << std::endl;

    std::cout << __LINE__ << std::endl;
    UNLESS(x == 3).FIX(caller);
    std::cout << __LINE__ << std::endl;
  }

  std::cout << __LINE__ << std::endl;
  UNLESS(x == 3).FIX(caller);
  std::cout << __LINE__ << std::endl;

  return 0;
}
