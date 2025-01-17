#define USING_IMKLIB_LOGGING_IMK_LOG

#define IMK_SLUG_EXTERN_ROOT_DIR imklib
#include "imklib/IMK_slug_index_ref.h"

#include IMK_SLUG_LOG

int main(void) {
  Log(LOG_TRACE, "Tracing program flow");
  Log(LOG_INFO, "Printing some output value");
  Log(LOG_DEBUG, "Debugging something");
  Log(LOG_WARN, "Something minor has gone wrong");
  Log(LOG_ERROR, "Oh no, something major has gone wrong");
  Log(LOG_FATAL, "You cant mask me");

  IMK_LogSetMin(LOG_WARN);
  Log(LOG_TRACE, "Hello world");
  Log1(LOG_WARN, "This is %s", "Global logger");
  Log3(LOG_FATAL, "%d^2 + %d^2 = %d^2", 3987, 4365, 4472);

  IMK_LogClearMask(LOG_MASK_ALL);
  Log(LOG_TRACE, "Tracing program flow");
  Log(LOG_INFO, "Printing some output value");
  Log(LOG_DEBUG, "Debugging something");
  Log(LOG_WARN, "Something minor has gone wrong");
  Log(LOG_ERROR, "Oh no, something major has gone wrong");
  Log(LOG_FATAL, "You cant mask me");
  return 0;
}
