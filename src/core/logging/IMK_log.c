#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define USING_NAMESPACE_IMK_LOG
#define USING_NAMESPACE_IMK_ANSI_STYLE

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_slug_index_ref.h"

#include SLUG_IMK_HEADER_LOG
#include SLUG_IMK_HEADER_INTS
#include SLUG_IMK_HEADER_ANSI_STYLE

static u8 log_levelmsk = LOG_MASK_ALL;

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
  auto time_t rawtime = {0};
  register struct tm const *timeinfo = NULL;

  if ((level > LOG_FATAL) || ((log_levelmsk & (1 << level)) == 0)) {
    return;
  }

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  fprintf(fp, "%02d:%02d:%02d %-5s %s:%d: ", timeinfo->tm_hour,
          timeinfo->tm_min, timeinfo->tm_sec, level_strings[level], file, line);
  vfprintf(fp, fmt, args);
  fprintf(fp, "\n");
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

  if ((level > LOG_FATAL) || ((log_levelmsk & (1 << level)) == 0)) {
    return;
  }

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  fprintf(fp,
          "%02d:%02d:%02d\x1b[0m %s%-5s" ANSI_RESET " \x1b[90m%s:%d:\x1b[0m ",
          timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
          level_colors[level], level_strings[level], file, line);
  vfprintf(fp, fmt, args);
  fprintf(fp, "\n");
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
  log_levelmsk = levelmsk;
  log_levelmsk |= LOG_MASK_FATAL;
}

void IMK_LogSetMin(u8 level) {
  log_levelmsk = (u8)(((u8)-1) << level);
  log_levelmsk |= LOG_MASK_FATAL;
}

u8 IMK_LogGetMask(void) { return log_levelmsk; }

void IMK_LogAddMask(u8 levelmsk) {
  log_levelmsk |= levelmsk;
  log_levelmsk |= LOG_MASK_FATAL;
}

void IMK_LogClearMask(u8 levelmsk) {
  log_levelmsk &= ~levelmsk;
  log_levelmsk |= LOG_MASK_FATAL;
}
