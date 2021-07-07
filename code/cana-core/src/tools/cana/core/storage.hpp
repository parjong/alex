#ifndef __CANA_CORE_STORAGE_H__
#define __CANA_CORE_STORAGE_H__

#include <boost/filesystem.hpp>

namespace cana { namespace core {

  class storage
  {
    private:
      boost::filesystem::path _base;

    public:
      boost::filesystem::path resolve(const boost::filesystem::path &p) const;

    public:
      storage(const boost::filesystem::path &base);
      ~storage() = default;
  };

} }

#endif
