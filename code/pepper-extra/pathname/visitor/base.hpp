#ifndef __PEPPER_PATHNAME_VISITOR_H__
#define __PEPPER_PATHNAME_VISITOR_H__

#include "pepper/pathname/dir.forward.hpp"
#include "pepper/pathname/relative/base.hpp"

namespace pepper { namespace pathname { namespace visitor {

  struct base
  {
    base() = default;
    virtual ~base() = default;

    virtual void visit(const pathname::dir &base, const pathname::relative::file &file) = 0;
    virtual bool visit(const pathname::dir &base, const pathname::relative::dir  &dir) = 0;
  };

} } }

#endif
