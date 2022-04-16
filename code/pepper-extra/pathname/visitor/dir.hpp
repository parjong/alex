#ifndef __PEPPER_PATHNAME_DIR_VISITOR_H__
#define __PEPPER_PATHNAME_DIR_VISITOR_H__

#include "pepper/pathname/visitor/base.hpp"

#include <functional>

namespace pepper { namespace pathname { namespace visitor {

  class dir : public visitor::base
  {
    public:
      typedef std::function<void (const pathname::dir &, const pathname::relative::dir &)> func;

    private:
      func _fn;      
    public:
      dir(func fn) : _fn(fn)
      {
        // DO NOTHING
      };
      virtual ~dir() = default;

    public:
      virtual void visit(const pathname::dir &base, const pathname::relative::file &file) 
      {
        // DO NOTHING
      }

      virtual bool visit(const pathname::dir &base, const pathname::relative::dir  &dir)
      {
        _fn(base, dir);
        return false;
      }
  };

} } }

#endif
