#define USING_IMKLIB_CORE_IMK_STEAP
#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_CORE_IMK_SCOPE
#define USING_IMKLIB_CORE_IMK_MEM
#define USING_IMKLIB_LOGGING_IMK_LOG

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_slug_index_ref.h"

#include SLUG_IMK_HEADER_STEAP
#include SLUG_IMK_HEADER_PTR
#include SLUG_IMK_HEADER_SCOPE
#include SLUG_IMK_HEADER_MEM
#include SLUG_IMK_HEADER_LOG

int main(void) {
  SCOPE_INIT(scope, 8);
  Ptr p;
  SCOPE_ADD(scope, p);

  p = TypedAllocP("Any", NULL, 128, FORCE_HEAP);
  Log2(LOG_INFO, "Allocated %s@%p", GetTypeHint(p), p.raw);

  SCOPE_RET(scope, int, 0);
}
