#define USING_IMKLIB_LOGGING_IMK_MODLOG
#include "imklib/logging/IMK_modlog.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define USING_IMKLIB_LOGGING_IMK_ANSI_STYLE
#include "imklib/logging/IMK_ansi_style.h"

void IMK_ModLogv(LogModule *logger, u8 priority, char const *fmt, va_list args) {
  LogModuleLevel *level = NULL;
  if ((logger->mask & (1u << priority)) == 0u) {
    return;
  }
  for (level = logger->level; level <= &logger->level[MODULE_LOG_MAX_LEVEL]; level += 1u) {
    if (level->priority == priority) {
      break;
    }
  }
  if (level > &logger->level[MODULE_LOG_MAX_LEVEL]) {
    return;
  }
  printf("%s%s%s", level->pre_bg, level->pre_fg, level->prefix);
  printf("%s ", ANSI_RESET);
  printf("%s%s", level->txt_bg, level->txt_fg);
  vprintf(fmt, args);
  printf("%s", ANSI_RESET);
}

void IMK_ModLog(IMK_LogModule *logger, u8 priority, char const *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  IMK_ModLogv(logger, priority, fmt, args);
  va_end(args);
}

