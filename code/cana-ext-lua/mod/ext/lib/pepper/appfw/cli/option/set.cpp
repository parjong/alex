#include <pepper/appfw/cli/option/set.hpp>

#include <pepper/attr.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace appfw { namespace cli { namespace option {

  set::set(pepper::bucket::object<std::string, pepper::appfw::app::option::desc *> &bucket) : _bucket(bucket)
  {
    // DO NOTHING
  }

  void set::enroll(const std::string &name, pepper::appfw::app::option::desc &desc)
  {
    _bucket.insert(name, &desc);
  }

} } } }
