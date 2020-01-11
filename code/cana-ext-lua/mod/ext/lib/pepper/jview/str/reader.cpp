#include <pepper/jview/str/reader.hpp>

namespace pepper { namespace jview { namespace str {

  reader::reader(const jimage::object &image, const jpath::object &path) : _image{image}, _path{path}
  {
    // DO NOTHING
  }

  void reader::operator<<(const std::function<void (const std::string &)> &fn) const
  {
    _image.read(_path, fn);
  }

} } }
