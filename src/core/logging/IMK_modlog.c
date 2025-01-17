#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define USING_IMKLIB_LOGGING_IMK_MODLOG
#define USING_IMKLIB_LOGGING_IMK_ANSI_STYLE

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_slug_index_ref.h"

#include SLUG_IMK_HEADER_MODLOG
#include SLUG_IMK_HEADER_ANSI_STYLE

void IMK_ModLogv(LogModule *logger, u8 priority, char const *fmt,
                 va_list args) {
  LogModuleLevel *level = NULL;
  if ((logger->mask & (1u << priority)) == 0u) {
    return;
  }
  for (level = logger->level; level <= &logger->level[MODULE_LOG_MAX_LEVEL];
       level += 1u) {
    if (level->priority == priority) {
      break;
    }
  }
  if (level > &logger->level[MODULE_LOG_MAX_LEVEL]) {
    return;
  }
  printf("%s%s", level->pre_style, level->prefix);
  printf("%s ", ANSI_RESET);
  printf("%s", level->txt_style);
  vprintf(fmt, args);
  printf("%s", ANSI_RESET);
}

void IMK_ModLog(IMK_LogModule *logger, u8 priority, char const *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  IMK_ModLogv(logger, priority, fmt, args);
  va_end(args);
}
