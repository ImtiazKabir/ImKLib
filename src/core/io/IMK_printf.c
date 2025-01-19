#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#include SLUG_IMK_HEADER_MACROS

#define USING_NAMESPACE_IMK_CORE
#include SLUG_IMK_HEADER_CORE

static char internal_buffer[268435456] = {0};
static char *internal_buffer_start = internal_buffer;

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
  VSNPrintF(NULL, 0, fmt, ap);
  return fprintf(stream, "%s", internal_buffer_start);
}

int VSPrintF(char *str, char const *fmt, va_list ap) {
  VSNPrintF(NULL, 0, fmt, ap);
  return sprintf(str, "%s", internal_buffer_start);
}

static int ObjSpecifier(char *str, va_list ap) {
  Ptr ptr = va_arg(ap, Ptr);
  Ptr tostr = ToStrP(ptr, NULL, FORCE_HEAP);
  int ret = sprintf(str, "%s", (char *)tostr.raw);
  Drop(&ptr);
  Drop(&tostr);
  return ret;
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

static int vsprintf_(char const *fmt, va_list ap) {
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
    int n1, n2, n3;

    char *dupfmt = shortened(fmt, first_occur_index);
    n1 = vsprintf(internal_buffer_start, dupfmt, ap);
    internal_buffer_start += n1;
    free(dupfmt);

    n2 = first_handler(internal_buffer_start, ap);
    internal_buffer_start += n2;

    n3 = vsprintf_(fmt + first_occur_index + strlen(first_specifier), ap);
    internal_buffer_start += n3;
    
    return n1 + n2 + n3;
  } else {
    int n = vsprintf(internal_buffer_start, fmt, ap);
    internal_buffer_start += n;
    return n;
  }
}

int VSNPrintF(char *str, size_t size, char const *fmt, va_list ap) {
  char *pushed_buf_start = internal_buffer_start;
  int ret;
  ret = vsprintf_(fmt, ap);
  if (ret > 0 && str != NULL && size > 0) {
    size_t min = (size_t)ret < size - 1 ? (size_t)ret : size - 1;
    memcpy(str, pushed_buf_start, min);
    str[min] = '\0';
  }
  internal_buffer_start = pushed_buf_start;
  return ret;
}

