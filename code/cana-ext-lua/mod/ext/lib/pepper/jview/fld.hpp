#ifndef __PEPPER_JVIEW_FLD_H__
#define __PEPPER_JVIEW_FLD_H__

#include <pepper/jview/obj.hpp>
#include <pepper/jpath.hpp>

namespace pepper { namespace jview {

  class fld
  {
    private:
      pepper::jpath::object _path;

    public:
      fld(const jview::obj &o, const std::string &name);

    public:
      virtual ~fld() = default;

    public:
      const pepper::jpath::object &path(void) const;
  };

} }

#endif
