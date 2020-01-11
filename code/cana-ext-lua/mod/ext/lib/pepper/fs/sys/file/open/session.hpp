#ifndef __PEPPER_FS_SYS_FILE_OPEN_SESSION_H__
#define __PEPPER_FS_SYS_FILE_OPEN_SESSION_H__

#include <pepper/fs/core/file/open/session.hpp>

#include <fstream>

namespace pepper { namespace fs { namespace sys { namespace file { namespace open {

  class session : public pepper::fs::core::file::open::session
  {
    private:
      std::ifstream _is;

    public:
      session(const std::string &path) : _is{ path }
      {
        // DO NOTHING
      }

    public:
      virtual ~session() = default;

    public:
      virtual bool apply(const std::function<void (std::istream &is)> &fn)
      {
        if ( _is.is_open() )
        {
          fn(_is);
          return true;
        }

        return false;
      }
  };

} } } } } 

#endif
