#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#define USING_NAMESPACE_IMK_CORE
#include SLUG_IMK_HEADER_CORE

int main(void) {
  SCOPE_INIT(scope, 8);
  Ptr p;
  SCOPE_ADD(scope, p);

  p = TypedAllocP("Any", NULL, 128, FORCE_HEAP);
  Log2(LOG_INFO, "Allocated %s@%p", GetTypeHint(p), p.raw);

  SCOPE_RET(scope, int, 0);
}
