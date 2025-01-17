#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define IMK_SLUG_EXTERN_ROOT_DIR imklib
#include "imklib/IMK_slug_index_ref.h"

#include IMK_SLUG_PRINTF

static char internal_buffer[268435456];

int IMK_VSNPrintF(char *str, size_t size, char const *fmt, va_list ap) {
  int ret = -1;
  if (size > sizeof(internal_buffer)) {
    return ret;
  }
  ret = vsprintf(internal_buffer, fmt, ap);
  if (ret > 0 && str != NULL && size > 0) {
    size_t min = (size_t)ret < size - 1 ? (size_t)ret : size - 1;
    memcpy(str, internal_buffer, min);
    str[min] = '\0';
  }
  return ret;
}

int IMK_SNPrintF(char *str, size_t size, char const *fmt, ...) {
  va_list ap;
  int ret;
  va_start(ap, fmt);
  ret = IMK_VSNPrintF(str, size, fmt, ap);
  va_end(ap);
  return ret;
}
