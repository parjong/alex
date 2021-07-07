#ifndef __PEPPER_PATHNAME_RECURSIVE_FILE_VISITOR_H__
#define __PEPPER_PATHNAME_RECURSIVE_FILE_VISITOR_H__

#include "pepper/pathname/visitor/base.hpp"

#include <functional>

namespace pepper { namespace pathname { namespace visitor {

  class recursive_file : public visitor::base
  {
    public:
      typedef std::function<void (const pathname::dir &, const pathname::relative::file &)> func;

    private:
      func _fn;      
    public:
      recursive_file(func fn) : _fn(fn)
      {
        // DO NOTHING
      };
      virtual ~recursive_file() = default;

    public:
      virtual void visit(const pathname::dir &base, const pathname::relative::file &file) 
      {
        _fn(base, file);
      }

      virtual bool visit(const pathname::dir &base, const pathname::relative::dir  &dir)
      {
        return true;
      }
  };

} } }

#endif
