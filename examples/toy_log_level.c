#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#include <pthread.h>

#define USING_NAMESPACE_IMK_LOG
#include SLUG_IMK_HEADER_LOG

/*
 * This toy example shows how Log Level conditions are thread local
 * Here the main function disables any log that is less important than WARN
 * So it can not print Hello world from main thread
 * But the other thread is not affected by this.
 * So it gets to print its Hello world
 */

static void *start(void *arg) {
  Log1(LOG_TRACE, "Hello world from %s thread", arg);
  return NULL;
}

int main(void) {
  pthread_t thread;

  LogSetMin(LOG_WARN);
  Log(LOG_TRACE, "Hello world from main thread");

  pthread_create(&thread, NULL, start, (void *)"child");
  pthread_join(thread, NULL);

  return 0;
}
