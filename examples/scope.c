#define USING_IMKLIB_CORE_IMK_SCOPE
#define USING_IMKLIB_CORE_IMK_PTR

#include "imklib/core/IMK_Ptr.h"
#include "imklib/core/IMK_scope.h"

static Ptr FuncA(void) {
  SCOPE(10) scope = {0};
  Ptr a = {0};
  SCOPE_ADD(scope, a);

  a = PtrOwnRaw(malloc(10), PTR_HEAP);
  SCOPE_RET(scope, Ptr, PtrMove(&a));
}

static void FuncB(Ptr ptr) {
  SCOPE(5) scope = {0};
  SCOPE_ADD(scope, ptr);
  SCOPE_END(scope);
}

static void FuncC(Ptr ptr_b) {
  SCOPE(12) scope = {0};
  Ptr x = {0};
  SCOPE_ADD(scope, x);

  x = PtrBorrow(ptr_b);

  SCOPE_END(scope);
}

int main(void) {
  SCOPE(32) scope = {0};
  Ptr c = {0};
  SCOPE_ADD(scope, c);

  c = FuncA();
  FuncC(c);
  FuncB(PtrMove(&c));

  SCOPE_RET(scope, int, 0);
}
