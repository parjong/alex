#include "pepper/json/value/object.hpp"

namespace pepper { namespace json {

  void meta::add(field &f)
  {
    _fields.push_back( &f );
  }

  void meta::iter(std::function<void (field &)> fn) const
  {
    for (const auto &field : _fields)
    {
      fn( *field );
    }
  }

  /**
   *
   */
  void object::add(field &f)
  {
    _meta.add(f);
  }

  json::meta &object::meta(void)
  {
    return _meta;
  }

  void object::iter(std::function<void (field &)> fn) const
  {
    _meta.iter(fn);
  }

} }
