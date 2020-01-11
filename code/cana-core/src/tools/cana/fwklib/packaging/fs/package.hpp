#ifndef __CANA_FWKLIB_PACKAGING_FS_PACKAGE_H__
#define __CANA_FWKLIB_PACKAGING_FS_PACKAGE_H__

#include <cana/ext/package.hpp>

#include <boost/filesystem.hpp>

namespace cana { namespace fwklib { namespace packaging { namespace fs {

  class package : public cana::ext::package
  {
    private:
      boost::filesystem::path _base;

    public:
      package(const boost::filesystem::path &base);

    public:
      virtual ~package() = default;

    public:
      virtual std::string resolve(const std::string &p) const;
  };

} } } }

#endif
