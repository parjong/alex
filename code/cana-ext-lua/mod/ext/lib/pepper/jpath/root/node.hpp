#ifndef __PEPPER_JPATH_ROOT_NODE_H__
#define __PEPPER_JPATH_ROOT_NODE_H__

#include <pepper/jpath/node.hpp>

namespace pepper { namespace jpath { namespace root {

  struct node : public jpath::node
  {
    node() = default;
    virtual ~node() = default;

    virtual void accept(jpath::visitor &v) const;
  };

} } }

#endif
