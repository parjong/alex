#include <gtest/gtest.h>

#include <iostream>
#include <map>
#include <memory>

namespace eve
{

struct EventContext;

struct Event
{
  virtual ~Event() = default;

  virtual void occur(EventContext *) const = 0;
};

struct TimePoint
{
  virtual ~TimePoint() = default;

  virtual void trigger(std::unique_ptr<Event> &&) = 0;
};

struct EventContext
{
  virtual ~EventContext() = default;

  virtual uint32_t now(void) const = 0;

  // after(0)?
  virtual std::unique_ptr<TimePoint> after(uint32_t delta) = 0;
};

class Simulation final : private EventContext
{
private:
  uint32_t _elapsed = 0;

  // CLASS INVARIANT
  //
  // For all (K, V) in _queue, K >= _elapsed
  using EventQueue = std::multimap<uint32_t, std::unique_ptr<Event>>;
  EventQueue _queue;

private:
  uint32_t now(void) const { return _elapsed; }

  std::unique_ptr<TimePoint> after(uint32_t delta)
  {
    struct TimePointImpl : public TimePoint
    {
      EventQueue *_queue = nullptr;
      uint32_t _tick = 0;

      void trigger(std::unique_ptr<Event> &&e)
      {
        _queue->insert({_tick, std::move(e)});
      }
    };

    auto time_point = std::make_unique<TimePointImpl>();

    time_point->_tick = _elapsed + delta;
    time_point->_queue = &_queue;

    return time_point;
  }

public:
  Simulation(std::unique_ptr<Event> &&e)
  {
    _queue.insert({0, std::move(e)});
  }

public:
  void WaitForCompletion(void)
  {
    while (not _queue.empty())
    {
      auto it = _queue.lower_bound(_elapsed);

      _elapsed = it->first;

      it->second->occur(this);

      // TODO Call occur
      _queue.erase(it);
    }
  }
};

Simulation StartWith(std::unique_ptr<Event> &&e)
{
  return Simulation(std::move(e));
}

} // namespace eve

TEST(APITest, how_to_use)
{
  struct FinalEvent final : public eve::Event
  {
    void occur(eve::EventContext *ctx) const
    {
      std::cout << "Final event is at " << ctx->now() << std::endl;
      return;
    }
  };

  struct FirstEvent final : public eve::Event
  {
    void occur(eve::EventContext *ctx) const
    {
      std::cout << "First event is at " << ctx->now() << std::endl;
      ctx->after(10)->trigger(std::make_unique<FinalEvent>());
      return;
    }
  };

  eve::StartWith(std::make_unique<FirstEvent>()).WaitForCompletion();
}
