#include <stdlib.h>

#define USING_NAMESPACE_IMK_PTR
#define USING_NAMESPACE_IMK_LOG

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_slug_index_ref.h"

#include SLUG_IMK_HEADER_PTR
#include SLUG_IMK_HEADER_LOG

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
