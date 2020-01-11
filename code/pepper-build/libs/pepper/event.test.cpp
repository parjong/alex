#include <pepper/testing.hpp>
#include <pepper/event.hpp>
#include <pepper/attr.hpp>
#include <pepper/mem.hpp>

COLLECTION(eventtests)
{
  struct observer : public pepper::event::observer<int>
  {
    pepper::attr::value::accessor<int> num;

    virtual void notify(const int &num)
    {
      this->num = num;
    };

    observer(const int &n)
    {
      num = n;
    }
    
    virtual ~observer() = default;
  };

  FACT(usage)
  {
    pepper::event::topic<int> t;

    auto o1 = pepper::mem::shared::make<::observer>( 0 );
    auto o2 = pepper::mem::shared::make<::observer>( 0 );

    t.connect( o1 );
    t.connect( o2 );

    EXPECT_EQ( o1->num(), 0 );
    EXPECT_EQ( o2->num(), 0 );

    t.publish( 64 );

    EXPECT_EQ( o1->num(), 64 );
    EXPECT_EQ( o2->num(), 64 );
  }
}
