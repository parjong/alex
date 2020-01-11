#ifndef __PEPPER_FS_CORE_SERVICE_H__
#define __PEPPER_FS_CORE_SERVICE_H__

#include <pepper/fs/core/file/service.hpp>

namespace pepper { namespace fs { namespace core {

  struct service
  {
    service() = default;
    virtual ~service() = default;

    virtual fs::core::file::service &file() = 0;
  };

} } }

#endif
