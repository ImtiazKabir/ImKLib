#define USING_IMKLIB_CORE_IMK_STEAP
#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_CORE_IMK_SCOPE
#define USING_IMKLIB_CORE_IMK_MEM
#define USING_IMKLIB_LOGGING_IMK_LOG

#define IMK_SLUG_EXTERN_ROOT_DIR imklib
#include "imklib/IMK_slug_index_ref.h"

#include IMK_SLUG_SCOPE
#include IMK_SLUG_STEAP
#include IMK_SLUG_MEM
#include IMK_SLUG_LOG
#include IMK_SLUG_PTR

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
