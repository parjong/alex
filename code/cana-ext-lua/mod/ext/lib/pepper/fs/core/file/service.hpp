#ifndef __PEPPER_FS_CORE_FILE_SERVICE_H__
#define __PEPPER_FS_CORE_FILE_SERVICE_H__

#include <pepper/fs/core/file/make/session.hpp>
#include <pepper/fs/core/file/open/session.hpp>

#include <string>

namespace pepper { namespace fs { namespace core { namespace file {

  struct service
  {
    service() = default;
    virtual ~service() = default;

    virtual file::make::region make(const std::string &path) const = 0;
    virtual file::open::region open(const std::string &path) const = 0;
  };

} } } }

#endif
