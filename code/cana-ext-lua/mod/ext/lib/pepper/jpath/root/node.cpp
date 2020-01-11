#include <pepper/jpath/root/node.hpp>
#include <pepper/jpath/visitor.hpp>

namespace pepper { namespace jpath { namespace root {
  
  void node::accept(jpath::visitor &v) const
  {
    v.visit(*this);
  }

} } }
