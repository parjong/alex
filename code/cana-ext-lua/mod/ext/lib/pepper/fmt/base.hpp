#ifndef __PEPPER_FMT_BASE_H__
#define __PEPPER_FMT_BASE_H__

#include <ostream>

namespace pepper { namespace fmt {

  struct base
  {
    base() = default;
    virtual ~base() = default;

    virtual std::ostream &output(std::ostream &os) const = 0;
  };

  std::ostream &operator<<(std::ostream &os, const base &o);

} }

#endif
