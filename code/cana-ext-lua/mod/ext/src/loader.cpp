#include "loader.hpp"
#include "app.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>

#if 0
{
  "path" : "..."
}
#endif

namespace cana { namespace binder { namespace lua {

  std::unique_ptr<ext::app> loader::load(const cana::ext::service &service) const
  {
    boost::filesystem::ifstream ifs{service.package()->resolve("plugin.json")};

    boost::property_tree::ptree doc;
    boost::property_tree::read_json(ifs, doc);

    std::string entry_value = doc.get<std::string>("path");
    boost::filesystem::path entry_path = service.package()->resolve(entry_value);

    return std::unique_ptr<ext::app>{new lua::app{service.logger(), entry_path.native()}};
  }

} } }
