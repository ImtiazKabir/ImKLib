#include <stdlib.h>

#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_LOGGING_IMK_LOG

#define IMK_SLUG_EXTERN_ROOT_DIR imklib
#include "imklib/IMK_slug_index_ref.h"

#include IMK_SLUG_PTR
#include IMK_SLUG_LOG

static Ptr FuncA(void) {
  Ptr a = PtrOwnRaw(malloc(10), PTR_HEAP);
  Ptr b = PtrMove(&a);
  Drop(&a);
  return b;
}

static void FuncB(Ptr ptr) { Drop(&ptr); }

static void FuncC(Ptr ptr_b) {
  Ptr ptr = IMK_PtrBorrow(ptr_b);
  Drop(&ptr);
}

int main(void) {
  Ptr c = FuncA();
  FuncC(c);
  FuncB(PtrMove(&c));
  Drop(&c);
  return 0;
}
