#include <stdio.h>

typedef union {
  int c;
  int d[10];
} union_t;

struct test_struct2                                                             
{                                                                               
  int a;                                                                        
  int b;                                                                        
  union_t u;
};

int func_union(int x, union_t u) {
  printf("c = %d\n", u.c);
  for (int i = 0; i < 10; ++i) {
    printf("d[%d] = %d\n", i, u.d[i]);
  }
  return 0;
}

int func(struct test_struct2 *p) {
  printf("a = %d\n", p->a);
  printf("b = %d\n", p->b);
  printf("c = %d\n", p->u.c);

  for (int i = 0; i < 10; ++i) {
    printf("d[%d] = %d\n", i, p->u.d[i]);
  }
  return 0;
}
