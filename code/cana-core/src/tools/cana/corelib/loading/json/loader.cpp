#include <cana/corelib/loading/json/loader.hpp>

#include <cana/fwklib/packaging/fs/package.hpp>
#include <cana/fwklib/packaging/fs/storage.hpp>
#include <cana/fwklib/packaging/fs/service.hpp>

#include <cana/logging/point.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#if 0
{
  "apps" :
  {
    "name 1" : { "type" : "...", "base" : "..." },
    "name 2" : { "type" : "...", "base" ; "..." },
    ...
    "name 3" : { "type" : "...", "base" ; "..." }
  }
}
#endif

namespace cana { namespace corelib { namespace loading { namespace json {

  loader::loader(std::istream &is, const json::package &package, const core::storage &storage) : _is(is), _package(package), _storage(storage)
  {
    // DO NOTHING
  }

  void loader::load(core::app::store &mgr, const core::binder::catalog &catalog)
  {
    static cana::logging::point log{__FUNCTION__};

    boost::property_tree::ptree doc;
    boost::property_tree::read_json(_is, doc);

    const auto &plugins = doc.get_child("apps");

    for (const auto &plugin : plugins)
    {
      std::string name = plugin.first;
      std::string type = plugin.second.get<std::string>("type");
      std::string base = plugin.second.get<std::string>("base");

      log.info("load '", type, "' plugin '", name, "' from '", base, "'");

      auto app_package = std::make_shared<fwklib::packaging::fs::package>(_package.resolve(base));
      auto app_storage = std::make_shared<fwklib::packaging::fs::storage>(_storage.resolve(name));
      fwklib::packaging::fs::service app_service{app_package, app_storage, "apploader"};

      auto add_fn = [&] (const cana::ext::loader &ld)
      {
        app_storage->make();

        mgr.add(ld.load(app_service));
      };

      catalog.get(type, add_fn);
    }

    return;
  }

} } } }
