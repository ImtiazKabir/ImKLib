#include "imklib/io/IMK_assert.h"

#include <errno.h>
#include <string.h>

#include "imklib/base/IMK_macros.h"

#define USING_IMKLIB_LOGGING_IMK_LOG
#include "imklib/logging/IMK_log.h"

#define USING_IMKLIB_ERROR_IMK_ERRNO
#include "imklib/error/IMK_errno.h"

void IMK_Panic(IMK_PanicStyle style, char const *msg) {
  u8 msk = LogGetMask();
  (void)style;
  LogSetMin(LOG_TRACE);
  LogF1(LOG_FATAL, stderr, "PANIC: %s", msg);
  if (errno != 0) {
    LogF1(LOG_ERROR, stderr, "ERRNO: %s", strerror(errno));
  }
  if (GetErrorCode() != 0) {
    LogF1(LOG_ERROR, stderr, "IMK_ERRNO: %s", GetErrorMessage());
  }
  fprintf(stderr, "\n");
  LogSetMask(msk);
  PROGRAM_CRASH();
}

