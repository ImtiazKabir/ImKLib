#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#include SLUG_IMK_HEADER_MACROS

#define USING_NAMESPACE_IMK_CORE
#include SLUG_IMK_HEADER_CORE

typedef struct {
  pthread_mutex_t lock; /* Underlying mutex lock */
  pthread_t owner;      /* Thread ID of the owner */
  int count;            /* Recursion count */
} recursive_mutex_t;

#define RECURSIVE_MUTEX_INITIALIZER {PTHREAD_MUTEX_INITIALIZER}

static void recursive_mutex_init(recursive_mutex_t *rm) {
  if (pthread_mutex_init(&rm->lock, NULL) != 0) {
    perror("Failed to initialize mutex");
    exit(EXIT_FAILURE);
  }
  rm->count = 0;
}

static void recursive_mutex_lock(recursive_mutex_t *rm) {
  if (rm->count && pthread_equal(rm->owner, pthread_self())) {
    /* If the current thread already owns the mutex, increment the count */
    rm->count++;
    return;
  }

  /* Otherwise, lock the underlying mutex */
  pthread_mutex_lock(&rm->lock);
  rm->owner = pthread_self();
  rm->count = 1;
}

static void recursive_mutex_unlock(recursive_mutex_t *rm) {
  if (!pthread_equal(rm->owner, pthread_self())) {
    /* Error: Unlocking a mutex not owned by this thread */
    fprintf(stderr, "Error: Thread does not own the mutex\n");
    exit(EXIT_FAILURE);
  }

  rm->count--;
  if (rm->count == 0) {
    /* Release ownership and unlock the mutex */
    pthread_mutex_unlock(&rm->lock);
  }
}

static void recursive_mutex_destroy(recursive_mutex_t *rm) {
  if (rm->count != 0) {
    fprintf(stderr, "Error: Destroying a locked mutex\n");
    exit(EXIT_FAILURE);
  }
  pthread_mutex_destroy(&rm->lock);
}

static char internal_buffer[268435456] = {0};
static char *internal_buffer_start = internal_buffer;
static recursive_mutex_t buf_mut = RECURSIVE_MUTEX_INITIALIZER;

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

int VPrintF(char const *fmt, va_list ap) { return VFPrintF(stdout, fmt, ap); }

int VFPrintF(FILE *stream, char const *fmt, va_list ap) {
  int ret;
  recursive_mutex_lock(&buf_mut);
  VSNPrintF(NULL, 0, fmt, ap);
  ret = fprintf(stream, "%s", internal_buffer_start);
  recursive_mutex_unlock(&buf_mut);
  return ret;
}

int VSPrintF(char *str, char const *fmt, va_list ap) {
  int ret;
  recursive_mutex_lock(&buf_mut);
  VSNPrintF(NULL, 0, fmt, ap);
  ret = sprintf(str, "%s", internal_buffer_start);
  recursive_mutex_unlock(&buf_mut);
  return ret;
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
  char *pushed_buf_start;
  int ret;
  recursive_mutex_lock(&buf_mut);
  pushed_buf_start = internal_buffer_start;
  ret = vsprintf_(fmt, ap);
  if (ret > 0 && str != NULL && size > 0) {
    size_t min = (size_t)ret < size - 1 ? (size_t)ret : size - 1;
    memcpy(str, pushed_buf_start, min);
    str[min] = '\0';
  }
  internal_buffer_start = pushed_buf_start;

  recursive_mutex_unlock(&buf_mut);
  return ret;
}
