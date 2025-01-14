#define USING_IMKLIB_CORE_IMK_STEAP
#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_CORE_IMK_SCOPE
#define USING_IMKLIB_CORE_IMK_MEM
#define USING_IMKLIB_LOGGING_IMK_LOG

#include "imklib/core/IMK_scope.h"
#include "imklib/core/IMK_steap.h"
#include "imklib/core/IMK_mem.h"
#include "imklib/logging/IMK_log.h"


int main(void) {
  SCOPE_INIT(scope, 8);
  Ptr p;
  SCOPE_ADD(scope, p);

  p = TypedAllocP("Any", NULL, 128, FORCE_HEAP);
  Log1(LOG_INFO, "Allocated at %p", p.raw);

  SCOPE_RET(scope, int, 0);
}


