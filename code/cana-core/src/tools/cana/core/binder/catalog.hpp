#ifndef __CANA_CORE_BINDER_CATALOG_H__
#define __CANA_CORE_BINDER_CATALOG_H__

#include <cana/ext/loader.hpp>

#include <functional>
#include <string>
#include <memory>
#include <map>

namespace cana { namespace core { namespace binder {

  class catalog
  {
    private:
      std::map<std::string, std::unique_ptr<cana::ext::loader>> _content;

    public:
      catalog()   = default;
      ~catalog()  = default;

    public:
      void set(const std::string &name, std::unique_ptr<cana::ext::loader> &&fac);
      void get(const std::string &name, const std::function<void (const cana::ext::loader &)> &cb) const;
  };

} } }

#endif
