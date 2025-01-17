#define USING_IMKLIB_CORE_IMK_STEAP
#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_CORE_IMK_SCOPE
#define USING_IMKLIB_CORE_IMK_MEM
#define USING_IMKLIB_LOGGING_IMK_LOG

#define IMK_SLUG_EXTERN_ROOT_DIR imklib
#include "imklib/IMK_slug_index_ref.h"

#include IMK_SLUG_STEAP
#include IMK_SLUG_PTR
#include IMK_SLUG_SCOPE
#include IMK_SLUG_MEM
#include IMK_SLUG_LOG

int main(void) {
  SCOPE_INIT(scope, 8);
  Ptr p;
  SCOPE_ADD(scope, p);

  p = TypedAllocP("Any", NULL, 128, FORCE_HEAP);
  Log2(LOG_INFO, "Allocated %s@%p", GetTypeHint(p), p.raw);

  SCOPE_RET(scope, int, 0);
}
