#ifndef __PEPPER_BENCHMARK_STOPWATCH_H__
#define __PEPPER_BENCHMARK_STOPWATCH_H__

#include <chrono>

namespace pepper
{
namespace benchmark
{

template<typename T> class stopwatch
{
public:
  stopwatch(T &out) : _out(out)
  {
    // DO NOTHING
  }

public:
  T &out(void) { return _out; }

private:
  T &_out;
};

template <typename T, typename Callable>
stopwatch<T> &operator<<(stopwatch<T> &&sw, Callable cb)
{
  auto start = std::chrono::steady_clock::now();
  cb();
  auto end = std::chrono::steady_clock::now();

  sw.out() += std::chrono::duration_cast<T>(end - start);
}

} // namespace benchmark
} // namespace pepper

#endif // __PEPPER_BENCHMARK_STOPWATCH_H__
