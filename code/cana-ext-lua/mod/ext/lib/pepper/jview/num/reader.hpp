#ifndef __PEPPER_JVIEW_NUM_READER_H__
#define __PEPPER_JVIEW_NUM_READER_H__

#include <pepper/jimage.hpp>
#include <pepper/jpath.hpp>

namespace pepper { namespace jview { namespace num {

  class reader
  {
    public:
      jimage::object _image;
      jpath::object  _path;

    public:
      reader(const jimage::object &image, const jpath::object &path);

    public:
      void operator<<(const std::function<void (int)> &fn) const;
  };

} } }

#endif
