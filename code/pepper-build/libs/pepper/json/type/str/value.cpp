#include <pepper/json/type/str/value.hpp>

namespace pepper { namespace json { namespace type { namespace str {

  value::value() : _str{ }
  {
    // DO NOTHING
  }


  value::operator const std::string &(void) const
  {
    return _str;
  }

  value &value::operator=(const std::string &str)
  {
    _str = str;

    return *this;
  }

  void value::load_from(const cursor::base &curr) 
  {
    _str = curr.get_reader().asString();
  }

  void value::dump_into(cursor::base &curr) const
  {
    curr.get_writer() = _str;
  }

} } } }
