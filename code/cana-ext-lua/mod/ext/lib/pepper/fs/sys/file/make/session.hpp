#ifndef __PEPPER_FS_SYS_FILE_MAKE_SESSION_H__
#define __PEPPER_FS_SYS_FILE_MAKE_SESSION_H__

#include <pepper/fs/core/file/make/session.hpp>

#include <fstream>

namespace pepper { namespace fs { namespace sys { namespace file { namespace make {

  class session : public pepper::fs::core::file::make::session
  {
    private:
      std::ofstream _os;

    public:
      session(const std::string &path) : _os{ path }
      {
        // TODO Return false if there is a file
      }

      virtual ~session() = default;

    public:
      virtual bool apply(const std::function<void (std::ostream &os)> &fn) override
      {
        fn(_os);
        return true;
      }
  };
    
} } } } } 

#endif
