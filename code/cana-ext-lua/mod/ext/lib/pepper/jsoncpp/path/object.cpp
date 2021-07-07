#include <pepper/jsoncpp/path/object.hpp>
#include <pepper/jsoncpp/path/root/accessor.hpp>
#include <pepper/jsoncpp/path/named/accessor.hpp>
#include <pepper/jsoncpp/path/indexed/accessor.hpp>

namespace pepper { namespace jsoncpp { namespace path {

  object::object()
  {
    _accessor = pepper::mem::shared::make<path::accessor, path::root::accessor>();
  }

  object::object(const std::shared_ptr<path::accessor> &accessor)
  {
    _accessor = accessor;
  }

  object::object(const object &o)
  {
    _accessor = o._accessor;
  }

  object object::named(const std::string &name) const
  {
    return pepper::mem::shared::make<path::accessor, path::named::accessor>(_accessor, name);
  }

  object object::indexed(int index) const
  {
    return pepper::mem::shared::make<path::accessor, path::indexed::accessor>(_accessor, index);
  }

  Json::Value &object::access(Json::Value &value) const
  {
    return _accessor->access(value);
  }

  const Json::Value &object::access(const Json::Value &value) const
  {
    return _accessor->access(value);
  }

} } }
