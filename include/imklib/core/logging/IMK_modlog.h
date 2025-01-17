#ifndef IMKLIB_LOGGING_IMK_MODLOG_H_
#define IMKLIB_LOGGING_IMK_MODLOG_H_

#include <stdarg.h>

#include "IMK_slug_index_ref.h"
#include SLUG_IMK_HEADER_INTS

typedef u32 IMK_LogModuleLevelType;
#define IMK_MODULE_LOG_MAX_LEVEL sizeof(IMK_LogModuleLevelType)

typedef struct {
  u8 priority;
  char const *prefix;
  char const *pre_style;
  char const *txt_style;
} IMK_LogModuleLevel;

typedef struct {
  IMK_LogModuleLevelType mask;
  IMK_LogModuleLevel level[IMK_MODULE_LOG_MAX_LEVEL];
} IMK_LogModule;

void IMK_ModLogv(IMK_LogModule *logger, u8 priority, char const *fmt,
                 va_list args);

void IMK_ModLog(IMK_LogModule *logger, u8 priority, char const *fmt, ...);

#ifdef USING_IMKLIB_LOGGING_IMK_MODLOG
typedef IMK_LogModuleLevel LogModuleLevel;
typedef IMK_LogModule LogModule;
typedef IMK_LogModuleLevelType LogModuleLevelType;
#define MODULE_LOG_MAX_LEVEL IMK_MODULE_LOG_MAX_LEVEL
#define ModLogV IMK_ModLogV
#define ModLog IMK_ModLog
#endif /* USING_IMKLIB_LOGGIN_IMK_MODLOG */

#endif /* !IMKLIB_LOGGING_IMK_MODLOG_H_ */
