#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#define USING_NAMESPACE_IMK_CORE
#include SLUG_IMK_HEADER_CORE

int main(void) {
  SCOPE_INIT(scope, 8);
  STACK_INIT(stack, 64);
  Ptr p1, p2, p3;
  SCOPE_ADD(scope, p1);
  SCOPE_ADD(scope, p2);
  SCOPE_ADD(scope, p3);

  p1 = VanillaAllocP(&stack, 48, PREFER_STACK);
  p2 = VanillaAllocP(&stack, 128, PREFER_STACK);
  p3 = VanillaAllocP(&stack, 8, PREFER_STACK);

  Log3(LOG_INFO, "p1 = %p, p2 = %p, p3 = %p", p1.raw, p2.raw, p3.raw);

  SCOPE_RET(scope, int, 0);
}
