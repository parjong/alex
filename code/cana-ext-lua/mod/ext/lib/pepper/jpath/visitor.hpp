#ifndef __PEPPER_JPATH_VISITOR_H__
#define __PEPPER_JPATH_VISITOR_H__

#include <pepper/jpath/root/node.hpp>
#include <pepper/jpath/named/node.hpp>
#include <pepper/jpath/indexed/node.hpp>

namespace pepper { namespace jpath {

  struct visitor
  {
    visitor() = default;
    virtual ~visitor() = default;

    virtual void visit(const root::node &) = 0;
    virtual void visit(const indexed::node &) = 0;
    virtual void visit(const named::node &) = 0;
  };

} }

#endif
