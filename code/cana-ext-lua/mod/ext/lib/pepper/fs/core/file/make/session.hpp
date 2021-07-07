#ifndef __PEPPER_FS_CORE_FILE_MAKE_SESSION_H__
#define __PEPPER_FS_CORE_FILE_MAKE_SESSION_H__

#include <pepper/mem.hpp>
#include <pepper/fun.hpp>

#include <istream>

namespace pepper { namespace fs { namespace core { namespace file { namespace make {

  struct session 
  {
    session() = default;
    virtual ~session() = default;

    virtual bool apply(const std::function<void (std::ostream &os)> &fn) = 0;
  };

  class region
  {
    private:
      std::shared_ptr<make::session> _sess;

    public:
      region(const std::shared_ptr<make::session> &sess) : _sess{ sess }
      {
        // DO NOTHING
      }

    public:
      bool operator<<(const std::function<void (std::ostream &os)> &fn) const
      {
        return _sess->apply(fn);
      }
  };
    
} } } } } 

#endif
