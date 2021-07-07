#ifndef __PEPPER_BENCHMARK_H__
#define __PEPPER_BENCHMARK_H__

#include <pepper/benchmark/stopwatch.hpp>

namespace pepper
{

template <typename T> benchmark::stopwatch<T> measure(T &out)
{
  return benchmark::stopwatch<T>(out);
}

} // namespace pepper

#endif // __PEPPER_BENCHMARK_H__
