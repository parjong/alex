#include "file.hpp"

namespace cana { namespace corelib { namespace log { namespace text {

  file::file(const std::string &name) : _os{name, std::ios_base::app}
  {
    // DO NOTHING
  }

  void file::write(const std::string &tag, const std::string &msg)
  {
    _os << tag << ", " << msg << std::endl;
  }

} } } }
