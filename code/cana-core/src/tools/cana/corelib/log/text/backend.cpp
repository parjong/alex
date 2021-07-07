#include "backend.hpp"
#include "factory.hpp"

#include <boost/filesystem.hpp>

namespace cana { namespace corelib { namespace log { namespace text {

  backend::backend(const core::storage &s) : _file{new text::file{s.resolve("cana.log").native()}}
  {
    _level = cana::log::LOG_NONE;
  }

  std::unique_ptr<cana::log::factory> backend::make(void) const
  {
    return std::unique_ptr<cana::log::factory>{new text::factory{_file, _level}};
  }

  void backend::set_level(const cana::log::level &level)
  {
    _level = level;
  }

} } } }
