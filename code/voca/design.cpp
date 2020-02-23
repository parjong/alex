#if 0
Design References
- Spark RDD
- The Volcano model in DBMS
- C++ Standard <range> library (in C++ 20)

Expected API style

std::vector<...> v;

auto sum =
  from_vector(v)
  | map(f)
  | filter(pred)
  | reduce(0, add)
;

Design Goal
- Easy to reuse standard "operator"s such as map, filter, reduce
- Easy to introduce a new operator

source : ... -> Dataset<T>
operator : Dataset<T> -> Dataset<U>
sink : Dataset<T> -> U;

Add a sink will trigger the whole execution!
#endif

#include <memory>

#include <fipe.hpp>

namespace
{

enum class Signal
{
  BeginningOfData,  // The Beginning of Data
  EndOfData,        // The End of Data
};

/**
 * Sink<T> *sink = ...
 * 
 * sink->feed(Signal::BeginningOfData);
 * sink->feed(...);
 * sink->feed(...);
 * ...
 * sink->feed(Signal::EndOfData);
 *
 */
template <typename T> struct Sink
{
  virtual ~Sink() = default;

  // Singal Feed
  virtual void feed(const Signal &) = 0;
  // Data Feed
  virtual void feed(const T &) = 0;
};

/**
 * SourceRef<T> src = ...
 *
 * src->scan(&sink);
 */
template <typename T> struct Source
{
  virtual ~Source() = default;

  virtual void scan(Sink<T> *) const = 0;
};

template <typename T> using SourceRef = std::shared_ptr<Source<T>>;

} // namespace

namespace
{

template <typename T> struct Filtered
{
  struct Functor
  {
    int operator()(const std::shared_ptr<Source<T>> &) const
    {
      throw std::runtime_error{"Not implemented, yet"};
    }
  };
};

template <typename T>
typename Filtered<T>::Functor filter(std::function<bool (const T &)> &&p)
{
  return typename Filtered<T>::Functor{};
}

} // namespace

namespace
{

// Action takes a Source and returns a non-Source value
struct SumAction
{
  int operator()(const std::shared_ptr<Source<int>> &source) const
  {
    struct SinkImpl final : public Sink<int>
    {
      int accum = 0;

      // TODO Validate 
      void feed(const Signal &) final { return; }
      void feed(const int &v) final { accum += v; }
    };

    SinkImpl sink;
      
    source->scan(&sink);

    return sink.accum;
  }
};

SumAction sum(void) { return SumAction{}; }

} // namespace

#include <iostream>

namespace
{

struct SampleSource final : public Source<int>
{
  void scan(Sink<int> *sink) const final
  {
    sink->feed(Signal::BeginningOfData);
    sink->feed(1);
    sink->feed(2);
    sink->feed(3);
    sink->feed(Signal::EndOfData);
  }
};

}

int main(int argc, char **argv)
{
  auto source = std::make_shared<SampleSource>();

  auto obtained_sum = source | sum();
  
  if (obtained_sum != 6)
  {
    std::cout << "FAIL!" << std::endl;
    return 255;
  }

  auto filtered_sum = 
    source 
    | filter<int>([] (const int &n) { return n % 2 == 0; })
    | sum();
  
  return 0;
}
