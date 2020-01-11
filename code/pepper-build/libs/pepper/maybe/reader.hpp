#ifndef __PEPPER_MAYBE_READER_H__
#define __PEPPER_MAYBE_READER_H__

#include <pepper/functional.hpp>

namespace pepper { namespace maybe {

  template <typename T> struct reader
  {
    reader() = default;
    virtual ~reader() = default;

    virtual bool filled(void) const = 0;

    typedef std::function<void (const T &)> probe;
    virtual bool read(const probe &fn) const = 0;
  };

} }

#endif
