#ifndef IMK_MODLOG_H_9RVMADL2AM07I8AI
#define IMK_MODLOG_H_9RVMADL2AM07I8AI

#include <stdarg.h>

#include "IMK_index_ref.slug"
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

#ifdef USING_NAMESPACE_IMK_MODLOG
#define LogModuleLevel IMK_LogModuleLevel
#define LogModule IMK_LogModule
#define LogModuleLevelType IMK_LogModuleLevelType
#define MODULE_LOG_MAX_LEVEL IMK_MODULE_LOG_MAX_LEVEL
#define ModLogV IMK_ModLogV
#define ModLog IMK_ModLog
#endif /* USING_NAMESPACE_IMK_MODLOG */

#endif /* !IMK_MODLOG_H_9RVMADL2AM07I8AI */
