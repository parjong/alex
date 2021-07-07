using System;

namespace Example
{
  class Hello
  {
    static void Main()
    {
      sample.func(1,2);

      SWIGTYPE_p_Pair p = sample.new_Pair();

      sample.Pair_x_set(p, 3);
      sample.Pair_y_set(p, 6);

      sample.func_2(p);

      sample.func_3(3, 4, sample.func_3_0_cb);
    }
  }
}
