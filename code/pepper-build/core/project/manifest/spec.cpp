#include <core/project/manifest/spec.hpp>

namespace core { namespace project { namespace manifest {

  spec::spec() : deps{ *this, "deps" }
  {
    // DO NOTHING
  }

} } }
