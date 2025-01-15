#define USING_IMKLIB_ERROR_IMK_ERROR
#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_CORE_IMK_MEM
#define USING_IMKLIB_CORE_IMK_STEAP
#define USING_IMKLIB_CORE_IMK_SCOPE
#define USING_IMKLIB_LOGGING_IMK_LOG
#define USING_IMKLIB_CORE_IMK_PARAMS

#include "imklib/error/IMK_error.h"
#include "imklib/core/IMK_ptr.h"
#include "imklib/core/IMK_mem.h"
#include "imklib/core/IMK_steap.h"
#include "imklib/core/IMK_scope.h"
#include "imklib/core/IMK_params.h"
#include "imklib/logging/IMK_log.h"

ERROR_DECLARE(MyError, Error)
ERROR_DEFINE(MyError, Error, 32, "Error: MyError")

int main(void) {
  SCOPE_INIT(scope, 8);
  STACK_INIT(stack, 100);
  Ptr err;
  SCOPE_ADD(scope, err);

  err = KlassAllocP(MyErrorKlass, &stack, PREFER_STACK, U32(2), PARAM_RPTR, &stack, PARAM_U32, PREFER_STACK);
  Log2(LOG_INFO, "%d %s", ((Error *)err.raw)->code, ((Error *)err.raw)->desc);

  SCOPE_RET(scope, int, 0);
}

