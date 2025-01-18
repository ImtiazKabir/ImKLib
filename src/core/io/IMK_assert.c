#include <errno.h>
#include <stdio.h>
#include <string.h>

#define USING_NAMESPACE_IMK_ASSERT
#define USING_NAMESPACE_IMK_LOG
#define USING_NAMESPACE_IMK_ERRNO

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#include SLUG_IMK_HEADER_ASSERT
#include SLUG_IMK_HEADER_INTS
#include SLUG_IMK_HEADER_MACROS
#include SLUG_IMK_HEADER_LOG
#include SLUG_IMK_HEADER_ERRNO

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
