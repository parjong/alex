#include "catalog.hpp"

namespace cana { namespace core { namespace binder {

  void catalog::set(const std::string &name, std::unique_ptr<cana::ext::loader> &&fac)
  {
    _content[name] = std::move(fac);
  }

  void catalog::get(const std::string &name, const std::function<void (const cana::ext::loader &)> &cb) const
  {
    auto it = _content.find(name);

    if (it != _content.end())
    {
      cb(*(it->second));
    }
  }

} } }
