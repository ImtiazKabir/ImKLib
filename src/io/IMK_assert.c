#include <stdio.h>
#define USING_IMKLIB_IO_IMK_ASSERT
#include "imklib/io/IMK_assert.h"

#include <errno.h>
#include <string.h>

#include "imklib/base/IMK_ints.h"
#include "imklib/base/IMK_macros.h"

#define USING_IMKLIB_LOGGING_IMK_LOG
#include "imklib/logging/IMK_log.h"

#define USING_IMKLIB_ERROR_IMK_ERRNO
#include "imklib/error/IMK_errno.h"

void Panic(char const *msg) {
  LogF1(LOG_FATAL, stderr, "PANIC: %s", msg);
  if (errno != 0) {
    LogF1(LOG_ERROR, stderr, "ERRNO: %s", strerror(errno));
  }
  if (GetErrorCode() != 0) {
    LogF1(LOG_ERROR, stderr, "IMK_ERRNO: %s", GetErrorMessage());
  }
  fprintf(stderr, "\n");
  PROGRAM_CRASH();
}

void PanicBox(char const *msg) {
  enum {TERMWD = 80};
  enum {BOXWD = 40};
  size_t len = strlen(msg);
  u8 num_chars_in_line = BOXWD - 2;
  u8 initial_space_count = (TERMWD - BOXWD) / 2;
  u8 printed_count = U8(0);
  u8 i;

  LogF1(LOG_FATAL, stderr, "Program panicked with the following message", msg);

  fprintf(stderr, "%*s+", initial_space_count, "");
  for (i = 0; i < num_chars_in_line; i++) {
    fputc('-', stderr);
  }
  fputs("+\n", stderr);

  while(printed_count < len) {
    fprintf(stderr, "%*s|%-*.*s|\n", initial_space_count, "", num_chars_in_line, num_chars_in_line, msg);
    printed_count += num_chars_in_line;
    msg += num_chars_in_line;
  }

  fprintf(stderr, "%*s+", initial_space_count, "");
  for (i = 0; i < num_chars_in_line; i++) {
    fputc('-', stderr);
  }
  fputs("+\n", stderr);
  
  if (errno != 0) {
    LogF1(LOG_ERROR, stderr, "ERRNO: %s", strerror(errno));
  }
  if (GetErrorCode() != 0) {
    LogF1(LOG_ERROR, stderr, "IMK_ERRNO: %s", GetErrorMessage());
  }
  fprintf(stderr, "\n");
  PROGRAM_CRASH();
}

