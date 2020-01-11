#include <pepper/json/type/num/value.hpp>

namespace pepper { namespace json { namespace type { namespace num {

  value::value() : _num{ 0 }
  {
    // DO NOTHING
  }

  value::value(int n) : _num{ n }
  {
    // DO NOTHING
  }

  value::operator int(void) const
  {
    return _num;
  }

  value &value::operator=(int n)
  {
    _num = n;

    return *this;
  }

  void value::load_from(const cursor::base &curr) 
  {
    _num = curr.get_reader().asInt();
  }

  void value::dump_into(cursor::base &curr) const
  {
    curr.get_writer() = _num;
  }

} } } }
