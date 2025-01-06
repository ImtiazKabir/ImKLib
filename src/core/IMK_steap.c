#define USING_IMKLIB_CORE_IMK_STEAP
#define USING_IMKLIB_CORE_IMK_PTR

#include "imklib/core/IMK_steap.h"
#include "imklib/core/IMK_ptr.h"

Ptr StackAlloc(void *stack_, size_t n) {
  STACK(1) *stack = stack_;
  if (stack == NULL || (size_t)stack->off + n >= stack->cap) {
    Ptr null_ptr = {0};
    return null_ptr;
  } else {
    char *ret = stack->mem + stack->off;
    stack->off += n;
    return PtrOwnRaw(ret, PTR_STACK);
  }
}

Ptr HeapAlloc(size_t n) { return PtrOwnRaw(calloc(n, 1), PTR_HEAP); }

Ptr SteapAlloc(void *stack, size_t n) {
  Ptr ptr = StackAlloc(stack, n);
  if (ptr.raw != NULL) {
    return ptr;
  }
  return HeapAlloc(n);
}
