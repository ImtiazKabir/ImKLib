#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#define USING_NAMESPACE_IMK_ASSERT

#include SLUG_IMK_HEADER_ASSERT
#include SLUG_IMK_HEADER_LOG

int main(void) {
  IMK_Log(IMK_LOG_TRACE, "This is printed without using namespace");

  /*
  Log(LOG_ERROR, "Uncomment this line to get a namespace error");
  */

#include SLUG_IMK_ATTACH_LOG
  Log(LOG_TRACE, "After attaching the namespace, you can use short names");
  IMK_Log(IMK_LOG_INFO, "But longer names also coexists");
#include SLUG_IMK_DETACH_LOG

  /*
  Log(LOG_ERROR, "But after detach, they are no longer available");
  */

  ASSERT_MSG(1, "If you use a USING_NAMESPACE directive before including a "
                "module, then it is permanently attached, so shorter names are "
                "available throughout the translation unit");
  IMK_ASSERT_MSG(1, "Like before, so does the longer versions");

#include SLUG_IMK_ATTACH_ASSERT
  ASSERT_MSG(1, "In such case, attaching again, is useless");
#include SLUG_IMK_DETACH_ASSERT
  ASSERT_MSG(1, "But so is detaching, it is permanently attached");

  return 0;
}
