#include <cana/rt/preload/record.hpp>

namespace cana { namespace rt { namespace preload {

  record::record(const boost::filesystem::path &image, char **argv, char **envp) : _arg{argv}, _env{envp}
  {
    _image = image;
  }

  const std::string &record::image(void) const
  {
    return _image.native();
  }

  const preload::arg &record::arg(void) const
  {
    return _arg;
  }

  const preload::env &record::env(void) const
  {
    return _env;
  }

} } }
