#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#define USING_NAMESPACE_IMK_CORE
#include SLUG_IMK_HEADER_CORE

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
