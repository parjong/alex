#ifndef __CANA_FWKLIB_PACKAGING_FS_SERVICE_H__
#define __CANA_FWKLIB_PACKAGING_FS_SERVICE_H__

#include <cana/ext/service.hpp>

namespace cana { namespace fwklib { namespace packaging { namespace fs {

  class service : public cana::ext::service
  {
    private:
      std::shared_ptr<cana::ext::package> _package;
      std::shared_ptr<cana::ext::storage> _storage;

      std::string _logname;

    public:
      service(const std::shared_ptr<cana::ext::package> &,
              const std::shared_ptr<cana::ext::storage> &,
              const std::string &logname);

    public:
      virtual ~service() = default;

    public:
      virtual const std::shared_ptr<cana::ext::package> &package(void) const;
      virtual const std::shared_ptr<cana::ext::storage> &storage(void) const;

      virtual cana::ext::logger logger(void) const;
  };

} } } }

#endif
