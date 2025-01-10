#define USING_IMKLIB_OPTRES_IMK_OPTION
#include "imklib/optres/IMK_option.h"

struct ComplexNumber {
  int x;
  int y;
};

OPTION_DECLARE(OptCmplx, struct ComplexNumber)
typedef struct OptCmplx OptCmplx;
OPTION_DEFINE(OptCmplx, struct ComplexNumber)

static OptInt Foo(int p) {
  if (p == 0) {
    return OptInt_Some(10);
  }
  return OptInt_None();
}

static OptCmplx Bar(void) {
  OptInt t = OptInt_None();
  OPTION_TRY(t, OptInt, Foo(0), OptCmplx);
  {
    struct ComplexNumber c = {2, 3};
    c.x = OptInt_Unwrap(t);
    return OptCmplx_Some(c);
  }
}

int main(void) {
  struct ComplexNumber origin = {0};
  struct ComplexNumber z = OptCmplx_UnwrapOr(Bar(), origin);
  (void)z;
  OptCmplx_Expect(OptCmplx_None(), "Wow it works");
  return 0;
}
