#ifndef __PEPPER_MEM_UNIQUE_UTILS_H__
#define __PEPPER_MEM_UNIQUE_UTILS_H__

#include <memory>

namespace pepper { namespace mem { namespace unique {

  template <typename Base, typename Derived = Base, typename... Args>
    std::unique_ptr<Base> make(Args&&... args)
  {
    return std::unique_ptr<Base>( new Derived{ args... } );
  }

} } }

#endif
