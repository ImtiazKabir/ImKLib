#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#define USING_NAMESPACE_IMK_PRINTF
#include SLUG_IMK_HEADER_PRINTF

#include SLUG_IMK_HEADER_MACROS

static char internal_buffer[268435456];

int PrintF(char const *fmt, ...) {
  va_list ap;
  int ret;
  va_start(ap, fmt);
  ret = VPrintF(fmt, ap);
  va_end(ap);
  return ret;
}

int FPrintF(FILE *stream, char const *fmt, ...) {
  va_list ap;
  int ret;
  va_start(ap, fmt);
  ret = VFPrintF(stream, fmt, ap);
  va_end(ap);
  return ret;
}

int SPrintF(char *str, char const *fmt, ...) {
  va_list ap;
  int ret;
  va_start(ap, fmt);
  ret = VSPrintF(str, fmt, ap);
  va_end(ap);
  return ret;
}

int SNPrintF(char *str, size_t size, char const *fmt, ...) {
  va_list ap;
  int ret;
  va_start(ap, fmt);
  ret = VSNPrintF(str, size, fmt, ap);
  va_end(ap);
  return ret;
}

int VPrintF(char const *fmt, va_list ap) {
  return VFPrintF(stdout, fmt, ap);
}

int VFPrintF(FILE *stream, char const *fmt, va_list ap) {
  size_t n;
  char *buf;
  int ret;
  va_list aq;

  __va_copy(aq, ap);
  n = (size_t)VSNPrintF(NULL, 0, fmt, aq);
  va_end(aq);

  buf = malloc(n + 1);
  VSNPrintF(buf, n + 1, fmt, ap);
  ret = fprintf(stream, "%s", buf);
  free(buf);

  return ret;
}

int VSPrintF(char *str, char const *fmt, va_list ap) {
  size_t n = (size_t)VSNPrintF(NULL, 0, fmt, ap);
  char *buf = malloc(n + 1);
  int ret;
  VSNPrintF(buf, n + 1, fmt, ap);
  ret = sprintf(str, "%s", buf);
  free(buf);
  return ret;
}

static int ObjSpecifier(char *str, va_list ap) {
  int n = va_arg(ap, int);
  return sprintf(str, "%d", n);
}

static char const *custom_specifiers[] = {"%obj"};
static int (*handlers[])(char *, va_list) = {ObjSpecifier};

static char *shortened(char const *src, size_t n) {
  /* Get the first n chars of src in a new heap allocated string */
  char *ret = malloc(n + 1);
  ret[n] = '\0';
  strncpy(ret, src, n);
  return ret;
}

static int vsprintf_(char *str, char const *fmt, va_list ap) {
  char const *first_specifier = NULL;
  int (*first_handler)(char *, va_list) = NULL;
  size_t first_occur_index;
  char const *f;

  for (f = fmt; *f != '\0'; f++) {
    size_t i;
    for (i = 0; i < ARRAY_COUNT(custom_specifiers); i++) {
      size_t n = strlen(custom_specifiers[i]);
      if (strncmp(f, custom_specifiers[i], n) == 0) {
        first_specifier = custom_specifiers[i];
        first_handler = handlers[i];
        first_occur_index = (size_t)(f - fmt);
        break;
      }
    }
    if (first_specifier) {
      break;
    }
  }

  if (first_specifier) {
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    char *dupfmt = shortened(fmt, first_occur_index);
    n1 = vsprintf(str, dupfmt, ap);
    free(dupfmt);
    n2 = first_handler(str + n1, ap);
    n3 = vsprintf_(str + n1 + n2, fmt + first_occur_index + strlen(first_specifier), ap);
    return n1 + n2 + n3;
  } else {
    return vsprintf(str, fmt, ap);
  }
}

int VSNPrintF(char *str, size_t size, char const *fmt, va_list ap) {
  int ret = -1;
  if (size > sizeof(internal_buffer)) {
    return -1;
  }
  ret = vsprintf_(internal_buffer, fmt, ap);
  if (ret > 0 && str != NULL && size > 0) {
    size_t min = (size_t)ret < size - 1 ? (size_t)ret : size - 1;
    memcpy(str, internal_buffer, min);
    str[min] = '\0';
  }
  return ret;
}

