#ifndef __PEPPER_FS_CORE_FILE_OPEN_SESSION_H__
#define __PEPPER_FS_CORE_FILE_OPEN_SESSION_H__

#include <pepper/mem.hpp>
#include <pepper/fun.hpp>

#include <iostream>

namespace pepper { namespace fs { namespace core { namespace file { namespace open {

  struct session 
  {
    session() = default;
    virtual ~session() = default;

    virtual bool apply(const std::function<void (std::istream &is)> &fn) = 0;
  };

  class region
  {
    private:
      std::shared_ptr<session> _sess;

    public:
      region(const std::shared_ptr<session> &sess) : _sess{ sess }
      {
        // DO NOTHING
      }

    public:
      bool operator<<(const std::function<void (std::istream &is)> &fn) const
      {
        return _sess->apply(fn);
      }
  };
    
} } } } } 

#endif
