//
// This example shows how to use "lapse" along with std::chrono.
//
#include <lapse.h>

#include <iostream>

void millisecond(void)
{
  std::chrono::milliseconds elapsed{0};

  unsigned count = (1 << 24);

  lapse::measure(elapsed) << [count] (void)
  {
    for (unsigned i = 0; i < count; ++i)
    {
      // DO NOTHING
    }
  };

  std::cout << count << " iterations take " << elapsed.count() << "ms" << std::endl;
}

void microsecond(void)
{
  std::chrono::microseconds elapsed{0};

  unsigned count = (1 << 24);

  lapse::measure(elapsed) << [count] (void)
  {
    for (unsigned i = 0; i < count; ++i)
    {
      // DO NOTHING
    }
  };

  std::cout << count << " iterations take " << elapsed.count() << "us" << std::endl;
}

int main(int argc, char **argv)
{
  millisecond();
  microsecond();
  return 0;
}
