#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define USING_NAMESPACE_IMK_LOG
#define USING_NAMESPACE_IMK_ANSI_STYLE
#define USING_NAMESPACE_IMK_PRINTF

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#include SLUG_IMK_HEADER_LOG
#include SLUG_IMK_HEADER_INTS
#include SLUG_IMK_HEADER_ANSI_STYLE
#include SLUG_IMK_HEADER_PRINTF

static pthread_key_t log_levelmsk_key;
static pthread_once_t log_levelmsk_key_once = PTHREAD_ONCE_INIT;
static pthread_mutex_t log_mut = PTHREAD_MUTEX_INITIALIZER;

static void MakeKey(void) { pthread_key_create(&log_levelmsk_key, free); }

static u8 *GetLevelMask(void) {
  u8 *msk;
  pthread_once(&log_levelmsk_key_once, MakeKey);
  msk = pthread_getspecific(log_levelmsk_key);
  if (msk == NULL) {
    msk = malloc(sizeof(*msk));
    *msk = LOG_MASK_ALL;
    pthread_setspecific(log_levelmsk_key, msk);
  }
  return msk;
}

static char const *level_strings[] = {"TRACE", "DEBUG", "INFO",
                                      "WARN",  "ERROR", "FATAL"};
static char const *level_colors[] = {
    ANSI_BG_CYAN ANSI_FG_BLACK,          /* TRACE */
    ANSI_BG_BRIGHT_BLUE ANSI_FG_BLACK,   /* DEBUG */
    ANSI_BG_BRIGHT_GREEN ANSI_FG_BLACK,  /* INFO */
    ANSI_BG_BRIGHT_YELLOW ANSI_FG_BLACK, /* WARN */
    ANSI_BG_RED ANSI_FG_BLACK,           /* FATAL */
    ANSI_BG_BRIGHT_RED ANSI_FG_BLACK     /* FATAL */
};

void IMK_LogVFBW(u8 level, FILE *fp, char const *file, int line,
                 char const *fmt, va_list args) {
  time_t rawtime = {0};
  struct tm const *timeinfo = NULL;
  u8 log_levelmsk = IMK_LogGetMask();

  pthread_once(&log_levelmsk_key_once, MakeKey);

  if ((level > LOG_FATAL) || ((log_levelmsk & (1 << level)) == 0)) {
    return;
  }

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  pthread_mutex_lock(&log_mut);
  fprintf(fp, "%02d:%02d:%02d %-5s %s:%d: ", timeinfo->tm_hour,
          timeinfo->tm_min, timeinfo->tm_sec, level_strings[level], file, line);
  VFPrintF(fp, fmt, args);
  fprintf(fp, "\n");
  pthread_mutex_unlock(&log_mut);
}

void IMK_LogVBW(u8 level, char const *file, int line, char const *fmt,
                va_list args) {
  IMK_LogVFBW(level, stdout, file, line, fmt, args);
}

void IMK_LogFBW(u8 level, FILE *fp, char const *file, int line, char const *fmt,
                ...) {
  va_list args = {0};
  va_start(args, fmt);
  IMK_LogVFBW(level, fp, file, line, fmt, args);
  va_end(args);
}

void IMK_LogBW(u8 level, char const *file, int line, char const *fmt, ...) {
  va_list args = {0};
  FILE *fp = level < LOG_MASK_WARN ? stdout : stderr;
  va_start(args, fmt);
  IMK_LogVFBW(level, fp, file, line, fmt, args);
  va_end(args);
}

void IMK_LogVFCol(u8 level, FILE *fp, char const *file, int line,
                  char const *fmt, va_list args) {
  time_t rawtime = {0};
  struct tm const *timeinfo = NULL;
  u8 log_levelmsk = IMK_LogGetMask();

  if ((level > LOG_FATAL) || ((log_levelmsk & (1 << level)) == 0)) {
    return;
  }

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  pthread_mutex_lock(&log_mut);
  fprintf(fp,
          "%02d:%02d:%02d " ANSI_RESET "%s%-5s" ANSI_RESET ANSI_FG_BRIGHT_BLACK
          " %s:%d: " ANSI_RESET,
          timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
          level_colors[level], level_strings[level], file, line);
  VFPrintF(fp, fmt, args);
  fprintf(fp, "\n");
  pthread_mutex_unlock(&log_mut);
}

void IMK_LogVCol(u8 level, char const *file, int line, char const *fmt,
                 va_list args) {
  IMK_LogVFCol(level, stdout, file, line, fmt, args);
}

void IMK_LogFCol(u8 level, FILE *fp, char const *file, int line,
                 char const *fmt, ...) {
  va_list args = {0};
  va_start(args, fmt);
  IMK_LogVFCol(level, fp, file, line, fmt, args);
  va_end(args);
}

void IMK_LogCol(u8 level, char const *file, int line, char const *fmt, ...) {
  auto va_list args = {0};
  FILE *fp = level < LOG_MASK_WARN ? stdout : stderr;
  va_start(args, fmt);
  IMK_LogVFCol(level, fp, file, line, fmt, args);
  va_end(args);
}

void IMK_LogSetMask(u8 levelmsk) {
  u8 *log_levelmsk = GetLevelMask();
  *log_levelmsk = levelmsk;
  *log_levelmsk |= LOG_MASK_FATAL;
}

void IMK_LogSetMin(u8 level) { IMK_LogSetMask((u8)(((u8)-1) << level)); }

u8 IMK_LogGetMask(void) { return *GetLevelMask(); }

void IMK_LogAddMask(u8 levelmsk) {
  IMK_LogSetMask(IMK_LogGetMask() | levelmsk);
}

void IMK_LogClearMask(u8 levelmsk) {
  IMK_LogSetMask(IMK_LogGetMask() & ~levelmsk);
}
