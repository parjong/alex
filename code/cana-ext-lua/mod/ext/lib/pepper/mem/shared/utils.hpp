#ifndef __PEPPER_MEM_SHARED_UTILS_H__
#define __PEPPER_MEM_SHARED_UTILS_H__

#include <memory>

namespace pepper { namespace mem { namespace shared {

  template <typename Base, typename Derived = Base, typename... Args> std::shared_ptr<Base> make(Args&&... args)
  {
    return std::shared_ptr<Base>( new Derived{ args... } );
  }

} } }

#endif
