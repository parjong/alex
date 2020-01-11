#ifndef __PEPPER_JVIEW_SEQ_FLD_H__
#define __PEPPER_JVIEW_SEQ_FLD_H__

#include <pepper/jview/seq/reader.hpp>
#include <pepper/jview/fld.hpp>

namespace pepper { namespace jview { namespace seq {

  class fld : public jview::fld
  {
    public:
      fld(const jview::obj &o, const std::string &name);

    public:
      virtual ~fld() = default;

    public:
      reader read(const pepper::jimage::object &image) const;
  };

} } }

#endif
