using System;

namespace Client
{
  public class Hello
  {
    public static void Main()
    {
//      var u = new toy.union_t();
//
//      u.d[0] = 5;
//      u.c = 4;
//
//      toy.sample.func_union(u);
//
//      var obj = new toy.test_struct2();
//
//      obj.a = 3;
//      obj.b = 4;
//
//      ((test_struct2.Internal *) obj.__Instance())->u.c =3;
//
//      toy.sample.func(obj);
        toy.sample.func(1, 2);

        toy.Pair obj = new toy.Pair();

        obj.x = 3;
        obj.y = 6;

        toy.sample.func_2(obj);

        toy.sample.func_3(3, 4, toy.sample.Internal.func_3_0_0); 
        //toy.toy.func_3(3, 4, toy.toy.func_3_0); 
    }
  }
}
