#include <pepper/jpath/indexed/node.hpp>
#include <pepper/jpath/visitor.hpp>

namespace pepper { namespace jpath { namespace indexed {

  node::node(const std::shared_ptr<jpath::node> &prev, int offset)
  {
    _prev   = prev;
    _offset = offset;
  }

  const jpath::node &node::prev(void) const
  {
    return *_prev;
  }
 
  int node::offset(void) const
  {
    return _offset;
  }

  void node::accept(jpath::visitor &v) const
  {
    v.visit(*this);
  }

} } }
