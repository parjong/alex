#include "loader.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>

#include <memory>

#include <dlfcn.h>

#if 0
{
  "path" : "..."
}
#endif

typedef std::unique_ptr<cana::ext::app> (*make_fn)(const cana::ext::service &);

namespace cana { namespace binder { namespace native {

  std::unique_ptr<ext::app> loader::load(const ext::service &service) const
  {
    auto log = service.logger();

    boost::filesystem::ifstream ifs{service.package()->resolve("plugin.json")};

    log.info("parse a JSON native app configuration");
    boost::property_tree::ptree doc;
    boost::property_tree::read_json(ifs, doc);

    std::string entry_value = doc.get<std::string>("path");
    boost::filesystem::path entry_path = service.package()->resolve(entry_value);

    void *hnd = dlopen(entry_path.c_str(), RTLD_LAZY);
    make_fn make = (make_fn)dlsym(hnd, "make");
    return make(service);
  }

} } }
