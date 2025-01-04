#define USING_IMKLIB_IO_IMK_ASSERT
#include "imklib/io/IMK_assert.h"

#include "imklib/error/IMK_errno.h"

int main(void) {
  ASSERT(1);
  ASSERT_MSG(1 == 1, "Silent");
  ASSERT_MSG(2 == 3, "Imtiaz Kabir");
  ASSERT_MSG(2 == 2, "Oh yes");
  return 0;
}

