#include <pepper/testing.hpp>
#include <pepper/random.hpp>
#include <pepper/linq.hpp>

COLLECTION(random)
{
  FACT(usage)
  {
    pepper::random::number::object rnd;

    EXPECT_EQ(pepper::linq::from(rnd).limit( 16 ).count(), 16 );
  }
}
