#include <pepper/random/number/object.hpp>
#include <pepper/random/number/data.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace random { namespace number {

  pepper::stream::data::bean<int> object::stream(void) const
  {
    return mem::shared::make<pepper::stream::data::object<int>, number::data::object>();
  }

} } }
