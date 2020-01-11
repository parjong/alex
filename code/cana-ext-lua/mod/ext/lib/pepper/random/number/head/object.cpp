#include <pepper/random/number/head/object.hpp>

#include <random>

namespace pepper { namespace random { namespace number { namespace head {

  void object::generate(void)
  { 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis;

    _value = dis(gen);
  }

  maybe::object<int> object::access(void) const
  {
    return maybe::some(_value);
  }

  void object::forward(void)
  {
    generate();
  }

  object::object()
  {
    generate();
  }

} } } } 
