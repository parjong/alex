#ifndef __CANA_CORELIB_BINDING_JSON_PACKAGE_H__
#define __CANA_CORELIB_BINDING_JSON_PACKAGE_H__

#include <boost/filesystem.hpp>

namespace cana { namespace corelib { namespace binding { namespace json {

  class package
  {
    private:
      boost::filesystem::path _base;

    public:
      boost::filesystem::path resolve(const boost::filesystem::path &p) const;

    public:
      package(const boost::filesystem::path &base);
      ~package() = default;
  };

} } } }

#endif
