#define USING_IMKLIB_ERROR_IMK_ERROR
#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_CORE_IMK_MEM
#define USING_IMKLIB_CORE_IMK_STEAP
#define USING_IMKLIB_CORE_IMK_SCOPE
#define USING_IMKLIB_LOGGING_IMK_LOG
#define USING_IMKLIB_CORE_IMK_PARAMS

#define IMK_SLUG_EXTERN_ROOT_DIR imklib
#include "imklib/IMK_slug_index_ref.h"

#include IMK_SLUG_ERROR
#include IMK_SLUG_PTR
#include IMK_SLUG_MEM
#include IMK_SLUG_STEAP
#include IMK_SLUG_SCOPE
#include IMK_SLUG_PARAMS
#include IMK_SLUG_LOG

ERROR_DECLARE(MyError, Error)
ERROR_DEFINE(MyError, Error, 32, "Error: MyError")

int main(void) {
  SCOPE_INIT(scope, 8);
  STACK_INIT(stack, 128);
  Ptr err;
  SCOPE_ADD(scope, err);

  err = KlassAllocP(MyErrorKlass, &stack, PREFER_STACK, U32(2), PARAM_RPTR,
                    &stack, PARAM_U32, PREFER_STACK);
  ErrorThrow(err, &stack, PREFER_STACK);

  SCOPE_RET(scope, int, 0);
}
