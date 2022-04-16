#include <stdio.h>

struct _payload {
  int data[16];
};

struct Pair {
  int x;
  int y;
  struct _payload *payload;
};

typedef struct {
  int padding;
} padding_t;

typedef int (*cb)(int, int, padding_t *);

int func(int x, int y) {
	return printf("NUM = %d (from %s)\n", x + y, __FUNCTION__);
}

int func_2(const struct Pair *p) {
	return printf("NUM = %d (from %s)\n", p->x + p->y, __FUNCTION__);
}

int func_3_0(int x, int y, padding_t *p) {
  printf("%s is called\n", __FUNCTION__);

  p->padding = x + y;

  return func(x, y);
}

int func_3(int x, int y, cb fn) {
  padding_t pad;

  return fn(x, y, &pad);
}
