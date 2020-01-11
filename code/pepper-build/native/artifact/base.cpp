#include <native/artifact/base.hpp>

namespace native { namespace artifact {

  void exe::accept(visitor &v) const
  {
    return v.visit( *this );
  }

  void lib::accept(visitor &v) const
  {
    return v.visit( *this );
  }

} }
