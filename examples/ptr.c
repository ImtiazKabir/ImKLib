#define USING_IMKLIB_CORE_PTR_IMK_PTR
#include "imklib/core/ptr/IMK_Ptr.h"

#include <stdlib.h>

#define USING_IMKLIB_LOGGING_IMK_LOG
#include "imklib/logging/IMK_log.h"

static Ptr FuncA(void) {
  Ptr a = PtrOwnRaw(malloc(10), 0);
  Ptr b = PtrTransfer(&a);
  PtrDrop(&a);
  return b;
}

static void FuncB(Ptr ptr) { PtrDrop(&ptr); }

static void FuncC(Ptr ptr_b) {
  Ptr ptr = IMK_PtrBorrow(ptr_b);
  PtrDrop(&ptr);
}

int main(void) {
  Ptr c = FuncA();
  FuncC(c);
  FuncB(PtrTransfer(&c));
  PtrDrop(&c);
  return 0;
}
