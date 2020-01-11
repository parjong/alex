#include <core/unit/manifest/spec.hpp>

namespace core { namespace unit { namespace manifest {

  spec::spec()
    : framework{ *this, "framework" }
    , type{ *this, "type" }
  {
    // DO NOTHING
  }

} } }
