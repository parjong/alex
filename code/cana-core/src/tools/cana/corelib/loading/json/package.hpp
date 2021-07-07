#ifndef __CANA_CORELIB_LOADING_JSON_PACKAGE_H__
#define __CANA_CORELIB_LOADING_JSON_PACKAGE_H__

#include <boost/filesystem.hpp>

namespace cana { namespace corelib { namespace loading { namespace json {

  class package
  {
    private:
      boost::filesystem::path _base;

    public:
      boost::filesystem::path resolve(const boost::filesystem::path &p) const;

    public:
      package(const boost::filesystem::path &);
      ~package() = default;
  };

} } } }

#endif
