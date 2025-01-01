#define USING_IMKLIB_LOGGING_IMK_LOG
#include "imklib/logging/IMK_log.h"

int main(void) {
  IMK_LogSetMin(LOG_WARN);
  Log(LOG_TRACE, "Hello world");
  Log1(LOG_WARN, "This is %s", "Global logger");
  Log3(LOG_FATAL, "%d^2 + %d^2 = %d^2", 3987, 4365, 4472);
  return 0;
}

