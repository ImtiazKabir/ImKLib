#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define USING_NAMESPACE_IMK_PRINTF
#include SLUG_IMK_HEADER_PRINTF

static void *start(void *arg) {
  char buf[100];
  size_t i;

  for (i = 0; i < 100; i++) {
    SPrintF(buf, "Hello world from %s (%lu)", (char *)arg, i);
    sleep((unsigned)(rand() % 2));
    PrintF("%s\n", buf);
  }

  return NULL;
}

int main(void) {
  pthread_t t1, t2;

  pthread_create(&t1, NULL, start, (char *)"T1");
  pthread_create(&t2, NULL, start, (char *)"T2");

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return 0;
}
