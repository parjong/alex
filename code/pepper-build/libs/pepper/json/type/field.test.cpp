#include <pepper/testing.hpp>
#include <pepper/json/type/field.hpp>
#include <pepper/json/type/num/value.hpp>

namespace js = pepper::json::type;

COLLECTION(jsonfieldtests)
{  
  struct sample : public js::obj::value
  {
    sample() : number( *this, "number" )
    {
      // DO NOTHING
    }
    virtual ~sample() = default;

    js::field<js::num::value> number;
  };

  FACT(create)
  {
    ::sample sample; 
  }
}
