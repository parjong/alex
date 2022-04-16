#ifndef __PEPPER_JVIEW_OBJ_H__
#define __PEPPER_JVIEW_OBJ_H__

#include <pepper/jpath.hpp>

namespace pepper { namespace jview {

  class obj
  {
    private:
      pepper::jpath::object _path;

    public:
      obj() = default;

    public:
      virtual ~obj() = default;

    public:
      const pepper::jpath::object &path(void) const;
  };

} }

#endif
