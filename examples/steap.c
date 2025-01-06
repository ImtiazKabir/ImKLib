#define USING_IMKLIB_CORE_IMK_STEAP
#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_CORE_IMK_SCOPE
#define USING_IMKLIB_LOGGING_IMK_LOG

#include "imklib/core/IMK_scope.h"
#include "imklib/core/IMK_steap.h"
#include "imklib/logging/IMK_log.h"

int main(void) {
  SCOPE_INIT(scope, 8);
  STACK_INIT(stack, 64);
  Ptr p1, p2, p3;
  SCOPE_ADD(scope, p1);
  SCOPE_ADD(scope, p2);
  SCOPE_ADD(scope, p3);

  p1 = SteapAlloc(&stack, 48);
  p2 = SteapAlloc(&stack, 128);
  p3 = SteapAlloc(&stack, 8);

  Log3(LOG_INFO, "p1 = %p, p2 = %p, p3 = %p", p1.raw, p2.raw, p3.raw);

  SCOPE_RET(scope, int, 0);
}
