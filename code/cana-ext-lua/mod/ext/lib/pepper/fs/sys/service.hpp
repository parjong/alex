#ifndef __PEPPER_FS_SYSTEM_SERVICE_H__
#define __PEPPER_FS_SYSTEM_SERVICE_H__

#include <pepper/fs/core/service.hpp>
#include <pepper/fs/sys/file/service.hpp>

namespace pepper { namespace fs { namespace sys {

  class service : public pepper::fs::core::service
  {
    private:
      pepper::fs::sys::file::service _file;

    public:
      service() = default;
      virtual ~service() = default;

    public:
      virtual fs::core::file::service &file(void) override
      {
        return _file;
      }
  };

} } }


#endif
