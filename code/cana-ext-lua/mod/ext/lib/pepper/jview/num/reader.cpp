#include <pepper/jview/num/reader.hpp>

namespace pepper { namespace jview { namespace num {

  reader::reader(const jimage::object &image, const jpath::object &path) : _image{image}, _path{path}
  {
    // DO NOTHING
  }

  void reader::operator<<(const std::function<void (int)> &fn) const
  {
    _image.read(_path, fn);
  }

} } }
