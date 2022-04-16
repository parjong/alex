#ifndef __PEPPER_JVIEW_NUM_FLD_H__
#define __PEPPER_JVIEW_NUM_FLD_H__

#include <pepper/jview/num/reader.hpp>
#include <pepper/jview/fld.hpp>
#include <pepper/jimage.hpp>

namespace pepper { namespace jview { namespace num {

  class fld : public jview::fld
  {
    public:
      fld(const jview::obj &, const std::string &);

    public:
      virtual ~fld() = default;

    public:
      reader read(const jimage::object &image) const;
  };

} } }

#endif
