#include <stdio.h>

int x = 2;

typedef struct {
  void *p;
} Something;

Something foo(void) {
  Something i;
  i.p = &x;
  return i;
}

int main(void) {
  return 0;
}

