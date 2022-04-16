#ifndef __CANA_FWKLIB_PACKAGING_FS_STORAGE_H__
#define __CANA_FWKLIB_PACKAGING_FS_STORAGE_H__

#include <cana/ext/storage.hpp>

#include <boost/filesystem.hpp>

namespace cana { namespace fwklib { namespace packaging { namespace fs {

  class storage : public cana::ext::storage
  {
    private:
      boost::filesystem::path _base;

    public:
      storage(const boost::filesystem::path &base);

    public:
      virtual ~storage() = default;

    public:
      virtual std::string resolve(const std::string &p) const;

    public:
      void make(void);
  };

} } } }

#endif
