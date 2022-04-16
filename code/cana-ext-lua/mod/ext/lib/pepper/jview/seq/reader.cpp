#include <pepper/jview/seq/reader.hpp>

namespace pepper { namespace jview { namespace seq {

  reader::reader(const jimage::object &image, const jpath::object &path) : _image{image}, _path{path}
  {
    // DO NOTHING
  }

  void reader::operator<<(const std::function<void (int)> &fn) const
  {
    auto outer_fn = [&] (int n, const jimage::object &)
    {
      fn(n);
    };

    _image.enumerate(_path, outer_fn);
  }

  void reader::operator<<(const std::function<void (const jpath::object &p, int, const jimage::object &)> &fn) const
  {
    auto enum_fn = [&] (int ind, const jimage::object &obj)
    {
      fn(_path, ind, obj);
    };

    _image.enumerate(_path, enum_fn);
  }

} } }
