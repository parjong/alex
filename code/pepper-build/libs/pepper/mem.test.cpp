#include <pepper/testing.hpp>
#include <pepper/functional.hpp>
#include <pepper/mem.hpp>

COLLECTION(mem)
{
  FACT(unique_make)
  {
    int count = 0;

    {
      auto obj = pepper::mem::unique::make<pepper::functional::finally>([&] (void) { ++count; });
    }

    EXPECT_EQ( count, 1 );
  }

  FACT(shared_make)
  {
    int count = 0;

    {
      auto o_1 = pepper::mem::shared::make<pepper::functional::finally>([&] (void) { ++count; });

      {
        auto o_2 = o_1;
      }

      EXPECT_EQ( count, 0 );
    }

    EXPECT_EQ( count, 1 );
  }

  struct base 
  {
    virtual int number(void) = 0;
  };

  struct derived : public base
  {
    int _number;

    derived(int number) : _number{ number }
    {
      // DO NOTHING
    }

    virtual int number(void)
    {
      return _number;
    }
  };

  FACT(unique_make_derived)
  {
    int number = 3;

    auto o = pepper::mem::unique::make<::base, ::derived>(number);

    EXPECT_EQ( o->number(), number );
  }

  FACT(shared_make_derived)
  {
    int number = 3;

    auto o = pepper::mem::shared::make<::base, ::derived>(number);

    EXPECT_EQ( o->number(), number );
  }

  struct factory : public pepper::mem::factory<int>
  {
    private:
      int _num;

    public:
      factory(int num) : _num{ num }
      {
        // DO NOTHING
      }

    public:
      virtual ~factory() = default;

    public:
      virtual std::unique_ptr<int> make(void) const
      {
        return pepper::mem::unique::make<int>( _num );
      }
  };

  FACT(factory_usage)
  {
    ::factory fac{ 128 };

    pepper::mem::use(fac) << [] (const int &n)
    {
      EXPECT_EQ( n, 128 );
    };
  }

  FACT(shared_bean_usage)
  {
    pepper::mem::shared::bean<int> b{ 
      pepper::mem::shared::make<int>(3)
    };

    EXPECT_EQ( b(), 3 );
  }
}
