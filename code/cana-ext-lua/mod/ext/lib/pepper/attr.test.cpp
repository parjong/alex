#include <pepper/testing.hpp>
#include <pepper/attr.hpp>
#include <pepper/mem.hpp>

COLLECTION(attr)
{
  struct object
  {
    pepper::attr::value::reader<int> number;

    object(int n) : number{ n }
    {
      // DO NOTHING
    }
  };

  FACT(direct_reader_basic)
  {
    object o{0x11223344};

    EXPECT_EQ(o.number(), 0x11223344);
  }

  namespace direct { namespace accessor {
  
    struct object
    {
      pepper::attr::value::accessor<int> number;

      object() = default;

      object(const int &n) : number{ n }
      {
        // DO NOTHING
      }
    };

    FACT(direct_accessor_basic)
    {
      object o;

      o.number = 3;

      EXPECT_EQ(o.number(), 3);
    }

    FACT(value_accessor_constructor)
    {
      object o{3};

      EXPECT_EQ(o.number(), 3);
    }

  } } 

  namespace lazy { namespace reader {

    struct object
    {
      pepper::attr::lazy::reader<int> number;

      object(int n) : number{[=](void) { return pepper::mem::unique::make<int>(n); }}
      {
        // DO NOTHING
      }
    };

    FACT(lazy_reader_basic)
    {
      object o{3};

      EXPECT_EQ(o.number(), 3);
    }

  } }

  namespace ref { namespace reader {

    struct object
    {
      pepper::attr::ref::reader<int> number;

      object(const int &n) : number{n}
      {
        // DO NOTHING
      }
    };

    FACT(ref_reader_basic)
    {
      int number;

      object o{number};

      number = 3;

      EXPECT_EQ(o.number(), 3);

      number = 5;

      EXPECT_EQ(o.number(), 5);
    }

  } }

  namespace ref { namespace accessor {

    struct object
    {
      pepper::attr::ref::accessor<int> number;

      object(int &n) : number{ n }
      {
        // DO NOTHING
      }
    };

    FACT(ref_accessor_basic)
    {
      int number = 0;

      object o{number};

      o.number = 5;

      EXPECT_EQ(number, 5);
      EXPECT_EQ(o.number(), 5);
    }

  } }
}

