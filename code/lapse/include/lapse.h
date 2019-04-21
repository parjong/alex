#ifndef __LAPSE_H__
#define __LAPSE_H__

#include <chrono>
#include <utility>

namespace lapse
{

template<class Rep, class Period> class Session
{
public:
  Session(std::chrono::duration<Rep, Period> *out) : _out{out}
  {
    // DO NOTHING
  }

public:
  template<typename Callable> void measure(Callable cb)
  {
    using namespace std::chrono;

    auto beg = steady_clock::now();
    cb();
    auto end = steady_clock::now();

    (*_out) += duration_cast<duration<Rep, Period>>(end - beg);
  }

private:
  std::chrono::duration<Rep, Period> *_out;
};

template<class Rep, class Period, typename Callable>
Session<Rep, Period> &operator<<(Session<Rep, Period> &&sess, Callable &&cb)
{
  sess.measure(std::forward<Callable>(cb));
  return sess;
}

template<class Rep, class Period>
Session<Rep, Period> measure(std::chrono::duration<Rep, Period> &out)
{
  return Session<Rep, Period>{&out};
}

} // namespace lapse

#endif // __LAPSE_H__
