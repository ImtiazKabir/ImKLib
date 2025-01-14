#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_LOGGING_IMK_LOG

#include <stdlib.h>

#include "imklib/core/IMK_ptr.h"
#include "imklib/logging/IMK_log.h"

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
