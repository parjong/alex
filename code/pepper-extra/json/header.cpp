#include "pepper/json/header.hpp"

namespace pepper { namespace json {

  header::header()
    : variables{ *this, "variables" }
  {
    // DO NOTHING
  }

} }
