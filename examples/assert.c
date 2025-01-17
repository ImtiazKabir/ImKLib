#define USING_IMKLIB_IO_IMK_ASSERT

#define IMK_SLUG_EXTERN_ROOT_DIR imklib
#include "imklib/IMK_slug_index_ref.h"

#include IMK_SLUG_ERRNO
#include IMK_SLUG_ASSERT

int main(void) {
  ASSERT(1);
  ASSERT_MSG(1 == 1, "Silent");
  ASSERT_MSG(2 == 3, "Imtiaz Kabir");
  ASSERT_MSG(2 == 2, "Oh yes");
  return 0;
}
