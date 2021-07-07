#ifndef __PEPPER_MEM_FACTORY_H__
#define __PEPPER_MEM_FACTORY_H__

#include <memory>

namespace pepper { namespace mem {

  template <typename T> struct factory
  {
    factory() = default;
    virtual ~factory()= default;

    virtual std::unique_ptr<T> make(void) const = 0;
  };

} }

#endif
