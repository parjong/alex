#include <pepper/testing.hpp>
#include <pepper/filter.hpp>
#include <pepper/mem.hpp>

COLLECTION(filter)
{
  template <int N> struct unit : public pepper::filter::unit<int>
  {
    public:
      virtual pepper::filter::action check(const int &n) const
      {
        return (n == N) 
          ? pepper::filter::action::ACCEPT 
          : pepper::filter::action::DELEGATE;
      };

    public:
      unit() = default;
      virtual ~unit() = default;
  };

  FACT(usage)
  {
    pepper::filter::chain<int, false> chain;

    chain
      .append( pepper::mem::unique::make<::unit<2>>() )
      .append( pepper::mem::unique::make<::unit<4>>() );

    EXPECT_FALSE( chain.check(1) );
    EXPECT_TRUE( chain.check(2) );
    EXPECT_TRUE( chain.check(4) );
  }
}
