#include <pepper/random/number/data/object.hpp>
#include <pepper/random/number/head.hpp>

#include <pepper/mem.hpp>

namespace pepper { namespace random { namespace number { namespace data {

  pepper::stream::head::bean<int> object::head(void) const
  {
    return mem::shared::make<pepper::stream::head::object<int>, pepper::random::number::head::object>( );
  }
  
} } } }
