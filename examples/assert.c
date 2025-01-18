#define USING_NAMESPACE_IMK_ASSERT

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#include SLUG_IMK_HEADER_ERRNO
#include SLUG_IMK_HEADER_ASSERT

int main(void) {
  ASSERT(1);
  ASSERT_MSG(1 == 1, "Silent");
  ASSERT_MSG(2 == 3, "Imtiaz Kabir");
  ASSERT_MSG(2 == 2, "Oh yes");
  return 0;
}
