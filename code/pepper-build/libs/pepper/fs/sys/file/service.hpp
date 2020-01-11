#ifndef __PEPPER_FS_SYSTEM_FILE_SERVICE_H__
#define __PEPPER_FS_SYSTEM_FILE_SERVICE_H__

#include <pepper/fs/core/file/service.hpp>

#include <string>

namespace pepper { namespace fs { namespace sys { namespace file {

  class service : public fs::core::file::service
  {
    public:
      service() = default;
      virtual ~service() = default;

    public:
      virtual pepper::fs::core::file::make::region make(const std::string &path) const override;
      virtual pepper::fs::core::file::open::region open(const std::string &path) const override;
  };

} } } }

#endif
