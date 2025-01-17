#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USING_IMKLIB_ERROR_IMK_ERRNO
#define USING_IMKLIB_LOGGING_IMK_LOG

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_slug_index_ref.h"

#include SLUG_IMK_HEADER_ERRNO
#include SLUG_IMK_HEADER_LOG

/* Thread-local storage keys for error code and error message */
static pthread_key_t errcode_key;
static pthread_key_t errmsg_key;
static pthread_once_t key_once = PTHREAD_ONCE_INIT;

static char *dupstr(char const *src) {
  return strcpy(calloc(strlen(src) + 1u, sizeof(*src)), src);
}

/* Initialize thread-local storage keys */
static void create_keys(void) {
  pthread_key_create(&errcode_key, NULL);
  pthread_key_create(&errmsg_key, free);
}

/* Set the thread-local error code and message */
void IMK_SetError(int errcode, char const *errmsg) {
  int *perr;
  char *msg;

  pthread_once(&key_once, create_keys);

  /* Set the error code */
  perr = pthread_getspecific(errcode_key);
  if (perr == NULL) {
    perr = (int *)malloc(sizeof(int));
    pthread_setspecific(errcode_key, perr);
  }
  *perr = errcode;

  /* Set the error message */
  msg = pthread_getspecific(errmsg_key);
  if (msg != NULL) {
    free(msg);
  }
  msg = dupstr(errmsg);
  pthread_setspecific(errmsg_key, msg);
}

/* Get the current thread-local error code */
int IMK_GetErrorCode(void) {
  int *perr;

  pthread_once(&key_once, create_keys);
  perr = pthread_getspecific(errcode_key);
  return perr ? *perr : 0;
}

/* Get the current thread-local error message */
char const *IMK_GetErrorMessage(void) {
  char *msg;

  pthread_once(&key_once, create_keys);
  msg = pthread_getspecific(errmsg_key);
  return msg ? msg : "Success";
}

/* Clear the error code and message */
void IMK_ClearError(void) {
  int *perr;
  char *msg;

  pthread_once(&key_once, create_keys);

  /* Clear the error code */
  perr = pthread_getspecific(errcode_key);
  if (perr != NULL) {
    free(perr);
    pthread_setspecific(errcode_key, NULL);
  }

  /* Free the error message buffer if it is not NULL */
  msg = pthread_getspecific(errmsg_key);
  if (msg != NULL) {
    free(msg);
    pthread_setspecific(errmsg_key, NULL);
  }
}

void IMK_PrintError(char const *str) {
  char *msg = pthread_getspecific(errmsg_key);
  if ((msg != NULL) && (*msg != '\0')) {
    LogF2(LOG_ERROR, stderr, "%s: %s\n", str, msg);
  }
}
