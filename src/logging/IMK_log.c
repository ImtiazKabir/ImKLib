#define USING_IMKLIB_LOGGING_IMK_LOG
#include "imklib/logging/IMK_log.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define USING_IMKLIB_LOGGING_IMK_ANSI_STYLE
#include "imklib/logging/IMK_ansi_style.h"

static unsigned char log_levelmsk = LOG_MASK_ALL;

static char const *level_strings[] = {"TRACE", "DEBUG", "INFO",
                                      "WARN",  "ERROR", "FATAL"};
static char const *level_colors[] = {ANSI_FG_BRIGHT_BLUE, ANSI_FG_CYAN, ANSI_FG_GREEN,
                                     ANSI_FG_YELLOW, ANSI_FG_RED, ANSI_FG_MAGENTA};

void IMK_LogvfBW(unsigned char level, FILE *fp, char const *file, int line,
                      char const *fmt, va_list args) {
  auto time_t rawtime = {0};
  register struct tm const *timeinfo = NULL;

  if ((level > LOG_FATAL) || ((log_levelmsk & (1 << level)) == 0)) {
    return;
  }

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  fprintf(fp, "%02d:%02d:%02d %-5s %s:%d: ", timeinfo->tm_hour,
                  timeinfo->tm_min, timeinfo->tm_sec, level_strings[level],
                  file, line);
  vfprintf(fp, fmt, args);
  fprintf(fp, "\n");
}

void IMK_LogvBW(unsigned char level, char const *file, int line,
                     char const *fmt, va_list args) {
  IMK_LogvfBW(level, stdout, file, line, fmt, args);
}

void IMK_LogfBW(unsigned char level, FILE *fp, char const *file, int line,
                     char const *fmt, ...) {
  va_list args = {0};
  va_start(args, fmt);
  IMK_LogvfBW(level, fp, file, line, fmt, args);
  va_end(args);
}

void IMK_LogBW(unsigned char level, char const *file, int line,
                    char const *fmt, ...) {
  va_list args = {0};
  FILE *fp = level < LOG_MASK_WARN ? stdout : stderr;
  va_start(args, fmt);
  IMK_LogvfBW(level, fp, file, line, fmt, args);
  va_end(args);
}

void IMK_LogvfCol(unsigned char level, FILE *fp, char const *file,
                       int line, char const *fmt, va_list args) {
  time_t rawtime = {0};
  struct tm const *timeinfo = NULL;

  if ((level > LOG_FATAL) || ((log_levelmsk & (1 << level)) == 0)) {
    return;
  }

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  fprintf(fp, "%02d:%02d:%02d\x1b[0m %s%-5s \x1b[90m%s:%d:\x1b[0m ",
                  timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
                  level_colors[level], level_strings[level], file, line);
  vfprintf(fp, fmt, args);
  fprintf(fp, "\n");
}

void IMK_LogvCol(unsigned char level, char const *file, int line,
                      char const *fmt, va_list args) {
  IMK_LogvfCol(level, stdout, file, line, fmt, args);
}

void IMK_LogfCol(unsigned char level, FILE *fp, char const *file, int line,
                      char const *fmt, ...) {
  va_list args = {0};
  va_start(args, fmt);
  IMK_LogvfCol(level, fp, file, line, fmt, args);
  va_end(args);
}

void IMK_LogCol(unsigned char level, char const *file, int line,
                     char const *fmt, ...) {
  auto va_list args = {0};
  FILE *fp = level < LOG_MASK_WARN ? stdout : stderr;
  va_start(args, fmt);
  IMK_LogvfCol(level, fp, file, line, fmt, args);
  va_end(args);
}

void IMK_LogSetMask(unsigned char levelmsk) { log_levelmsk = levelmsk; }

void IMK_LogSetMin(unsigned char level) {
  log_levelmsk = (unsigned char)(((unsigned char)-1) << level);
}

unsigned char IMK_LogGetMask(void) { return log_levelmsk; }

void IMK_LogAddMask(unsigned char levelmsk) { log_levelmsk |= levelmsk; }

void IMK_LogClearMask(unsigned char levelmsk) { log_levelmsk &= ~levelmsk; }

