#include "pepper/strcast.hpp"

#include <stdexcept>
#include <string>

namespace
{

// K::E (Element)
//   default contructible
//
// K::C (Converter)
//   std::system_error operator()(const char *s, T &)
//
// K::G (Generator)
//   T operator()(void)
template<typename K> // K?? Alg??
typename K::E safe_strcast(const char *s, typename K::C &&cvt, typename K::G &&gen)
{
  if (s == nullptr) return gen();

  typename K::E res{};
  std::error_code ec = cvt(s, res);
  return (ec.value() == 0) ? res : gen();
}

// DefaultConverter<T>?
struct IntConverter
{
  std::error_code operator()(const char *str, int &out) const
  {
    out = std::stoi(str);
    return std::error_code{};
  }
};

// DefaultGenerator<T>?
template<typename T> class StaticGenerator
{
public:
  StaticGenerator(const T &value) : _value{value}
  {
    // DO NOTHING
  }

public:
  T operator()(void) const { return _value; }

private:
  T _value;
};

} // namespace

namespace pepper
{

template<> int safe_strcast(const char *s, const int &v)
{
  struct K
  {
    using E = int;
    using C = IntConverter;
    using G = StaticGenerator<int>;
  };

  return ::safe_strcast<K>(s, IntConverter{}, StaticGenerator<int>{v});
}

} // namespace pepper
