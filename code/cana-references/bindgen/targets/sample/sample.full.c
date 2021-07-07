#include <stdio.h>

struct _payload {
  int data[16];
};

struct Pair {
  int x;
  int y;
  struct _payload *payload;
};

typedef enum {
  ERROR_COMMON_A,
  ERROR_COMMON_B,
  ERROR_MOBILE_A,
} error_t;

typedef enum {
  ERROR_A = ERROR_COMMON_A,
  ERROR_B = ERROR_COMMON_B,
} common_error_t;

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

int func_3_0(const struct Pair *p, cb fn) {
  printf("%s is called\n", __FUNCTION__);

  padding_t pad;

  return fn(p->x, p->y, &pad);
}

int func_3(int x, int y, cb fn) {
  padding_t pad;

  return fn(x, y, &pad);
}

int func_4(common_error_t code) {
  return code;
}
