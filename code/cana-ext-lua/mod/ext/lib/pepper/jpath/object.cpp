#include <pepper/jpath/object.hpp>
#include <pepper/jpath/root/node.hpp>
#include <pepper/jpath/named/node.hpp>
#include <pepper/jpath/indexed/node.hpp>

namespace pepper { namespace jpath {

  object::object()
  {
    _node = pepper::mem::shared::make<root::node>();
  }

  object::object(const std::shared_ptr<node> &node)
  {
    _node = node;
  }

  object::object(const object &o)
  {
    _node = o._node;
  }

  object object::indexed(int index) const
  {
    return pepper::mem::shared::make<jpath::node, jpath::indexed::node>(_node, index);
  }

  object object::named(const std::string &name) const
  {
    return pepper::mem::shared::make<jpath::node, jpath::named::node>(_node, name);
  }

  void object::accept(jpath::visitor &v) const
  {
    _node->accept(v);  
  }

  object make(void)
  {
    return object();
  }

} }
