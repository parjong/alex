#include <pepper/jimage/object.hpp>

namespace pepper { namespace jimage {

  object::object(const std::shared_ptr<jimage::accessor> &accessor)
  {
    _accessor = accessor;
  }

  object::object(const object &o)
  {
    _accessor = o._accessor;
  }

  void object::read(const jpath::object &p, const std::function<void (int)> &fn) const
  {
    _accessor->read(p, fn);
  }

  void object::read(const jpath::object &p, const std::function<void (const std::string &)> &fn) const
  {
    _accessor->read(p, fn);
  }

  void object::enumerate(const jpath::object &p, const std::function<void (int, const object &)> &fn) const
  {
    auto outer_fn = [&] (int num, const std::shared_ptr<accessor> &accessor)
    {
      object obj{accessor};

      fn(num, obj);
    };

    _accessor->enumerate(p, outer_fn);
  }

} }
