#ifndef __PEPPER_JVIEW_STR_FIELD_H__
#define __PEPPER_JVIEW_STR_FIELD_H__

#include <pepper/jview/str/reader.hpp>
#include <pepper/jview/fld.hpp>

namespace pepper { namespace jview { namespace str {

  class fld : public jview::fld
  {
    public:
      fld(const jview::obj &o, const std::string &name);

    public:
      virtual ~fld() = default;

    public:
      reader read(const jimage::object &image) const;
  };

} } }

#endif
