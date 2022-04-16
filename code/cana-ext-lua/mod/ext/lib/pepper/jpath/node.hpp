#ifndef __PEPPER_JPATH_NODE_H__
#define __PEPPER_JPATH_NODE_H__

namespace pepper { namespace jpath {

  class visitor;

  struct node
  {
    node() = default;
    virtual ~node() = default;

    virtual void accept(visitor &v) const = 0;
  };

} }

#endif
