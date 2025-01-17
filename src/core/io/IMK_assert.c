#include <errno.h>
#include <stdio.h>
#include <string.h>

#define USING_IMKLIB_IO_IMK_ASSERT
#define USING_IMKLIB_LOGGING_IMK_LOG
#define USING_IMKLIB_ERROR_IMK_ERRNO

#define IMK_SLUG_EXTERN_ROOT_DIR imklib
#include "imklib/IMK_slug_index_ref.h"

#include IMK_SLUG_ASSERT
#include IMK_SLUG_INTS
#include IMK_SLUG_MACROS
#include IMK_SLUG_LOG
#include IMK_SLUG_ERRNO

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
  enum { TERMWD = 80 };
  enum { BOXWD = 40 };
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

  while (printed_count < len) {
    fprintf(stderr, "%*s|%-*.*s|\n", initial_space_count, "", num_chars_in_line,
            num_chars_in_line, msg);
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
