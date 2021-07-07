#include <pepper/jpath/named/node.hpp>
#include <pepper/jpath/visitor.hpp>

namespace pepper { namespace jpath { namespace named {

  node::node(const std::shared_ptr<jpath::node> &prev, const std::string &name)
  {
    _prev = prev;
    _name = name;
  }

  const jpath::node &node::prev(void) const
  {
    return *_prev;
  }

  const std::string &node::name(void) const
  {
    return _name;
  }


  void node::accept(jpath::visitor &v) const
  {
    v.visit(*this);
  }

} } }
