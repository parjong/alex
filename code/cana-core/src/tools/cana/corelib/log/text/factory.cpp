#include "factory.hpp"
#include "stream.hpp"

namespace cana { namespace corelib { namespace log { namespace text {

  factory::factory(const std::shared_ptr<text::file> &file, const cana::log::level &level)
  {
    _file = file;
    _level = level;
  }

  std::unique_ptr<cana::log::stream> factory::make(const std::string &name) const
  {
    return std::unique_ptr<cana::log::stream>{new text::stream{_file, _level}};
  }

} } } }
