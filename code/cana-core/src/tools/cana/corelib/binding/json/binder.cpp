#include <cana/corelib/binding/json/binder.hpp>

#include <cana/logging/point.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <dlfcn.h>

#if 0
{
  "binders" : {
    "native" : "fwk/libfwk_native.so",
    "lua"    : "fwk/libfwk_lua.so"
  }
}
#endif

typedef std::unique_ptr<cana::ext::loader> (*entry)(void);

namespace cana { namespace corelib { namespace binding { namespace json {

  loader::loader(std::istream &is, const json::package &package) : _is(is), _package(package)
  {
    // DO NOTHING
  }

  void loader::load(core::binder::catalog &catalog)
  {
    static cana::logging::point log{__FUNCTION__};

    log.info("parse a JSON configuration");

    boost::property_tree::ptree doc;
    boost::property_tree::read_json(_is, doc);

    const auto &binders = doc.get_child("binders");

    for (const auto &binder : binders)
    {
      std::string name = binder.first;
      std::string path = binder.second.data();

      log.info("attempt to load '", name, "' from '", path, "'");

      void *hnd = dlopen(_package.resolve(path).c_str(), RTLD_LAZY);

      entry e = (entry) dlsym(hnd, "make");

      if (e != nullptr)
      {
        catalog.set(name, e());
        log.info("'", name, "' is loaded");
      }
    }
  }

} } } }
