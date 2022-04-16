#include <pepper/testing.hpp>
#include <pepper/linq.hpp>
#include <pepper/vector.hpp>
#include <pepper/fun.hpp>

#include <iostream>

COLLECTION(linq)
{
  FACT(flat_where)
  {
    pepper::vector::object<int> vec;

    vec.emplace(1).emplace(2).emplace(3).emplace(4);

    auto selected = 
      pepper::linq::from(vec)
      .where(pepper::fun::pred::gt(2));

    EXPECT_EQ( selected.count(), 2 );
  }

  FACT(nested_where)
  {
    pepper::vector::object<int> vec;

    vec.emplace(1).emplace(2).emplace(3).emplace(4);

    auto selected = 
      pepper::linq::from(vec)
      .where(pepper::fun::pred::gt(2))
      .where([] (int n) { return n % 2 != 0; });

    EXPECT_EQ( selected.count(), 1 );
  }

  FACT(transform)
  {
    pepper::vector::object<int> vec;

    vec.emplace('a').emplace('b').emplace('c');

    auto selected = 
      pepper::linq::from(vec)
      .select<int>( [] (char c) { return (c == 'a') ? 1 : 0; } )
      .where(pepper::fun::pred::gt(0));

    EXPECT_EQ( selected.count(), 1 );
  }

  FACT(limit)
  {
    pepper::vector::object<int> vec;

    for (int i = 0; i < 16; ++i)
    {
      vec.emplace(i);
    }

    auto ds = pepper::linq::from(vec);

    EXPECT_EQ( ds.limit(128).count(), 16 );
    EXPECT_EQ( ds.limit(4).count(), 4 );
  }

  FACT(foreach)
  {
    pepper::vector::object<int> vec;

    vec.emplace(1).emplace(1);

    int sum = 0;

    pepper::linq::from(vec).foreach( [&] (const int &num) { sum += num; } );

    EXPECT_EQ( sum, 2 );
  }

  FACT(exist_found)
  {
    pepper::vector::object<int> vec;

    vec.emplace(2).emplace(4).emplace(8);

    auto proof = 
      pepper::linq::from(vec)
      .exist( [] (const int &n) { std::cout << n << std::endl; return n > 3; } );

    EXPECT_TRUE( proof.filled() );
    EXPECT_EQ( proof, 4 );
  }

  FACT(exist_notfound)
  {
    pepper::vector::object<int> vec;

    vec.emplace(2).emplace(4).emplace(8);

    auto proof = 
      pepper::linq::from(vec)
      .exist(pepper::fun::pred::gt(16));

    EXPECT_FALSE( proof.filled() );
  }

  FACT(forall)
  {
    pepper::vector::object<int> vec;

    vec.emplace(2).emplace(4).emplace(8);

    EXPECT_TRUE( pepper::linq::from(vec).forall( [] (const int &n) { return n % 2 == 0; } ) );
  }
}
