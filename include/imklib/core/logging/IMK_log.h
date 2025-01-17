#ifndef IMK_LOG_H_UEK2076US6EIQ8Q7
#define IMK_LOG_H_UEK2076US6EIQ8Q7

#include <stdarg.h>
#include <stdio.h>

#include "IMK_slug_index_ref.h"
#include SLUG_IMK_HEADER_INTS

/* clang-format off */
#define IMK_LogF(level, fp, fmt)                                                  IMK_LogFCol(level, fp, __FILE__, __LINE__, fmt)
#define IMK_LogF1(level, fp, fmt, arg1)                                           IMK_LogFCol(level, fp, __FILE__, __LINE__, fmt, arg1)
#define IMK_LogF2(level, fp, fmt, arg1, arg2)                                     IMK_LogFCol(level, fp, __FILE__, __LINE__, fmt, arg1, arg2)
#define IMK_LogF3(level, fp, fmt, arg1, arg2, arg3)                               IMK_LogFCol(level, fp, __FILE__, __LINE__, fmt, arg1, arg2, arg3)
#define IMK_LogF4(level, fp, fmt, arg1, arg2, arg3, arg4)                         IMK_LogFCol(level, fp, __FILE__, __LINE__, fmt, arg1, arg2, arg3, arg4)
#define IMK_LogF5(level, fp, fmt, arg1, arg2, arg3, arg4, arg5)                   IMK_LogFCol(level, fp, __FILE__, __LINE__, fmt, arg1, arg2, arg3, arg4, arg5)
#define IMK_LogF6(level, fp, fmt, arg1, arg2, arg3, arg4, arg5, arg6)             IMK_LogFCol(level, fp, __FILE__, __LINE__, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define IMK_LogF7(level, fp, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7)       IMK_LogFCol(level, fp, __FILE__, __LINE__, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7)
#define IMK_LogF8(level, fp, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) IMK_LogFCol(level, fp, __FILE__, __LINE__, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)

#define IMK_Log(level, fmt)                                                  IMK_LogF(level, stdout, fmt)
#define IMK_Log1(level, fmt, arg1)                                           IMK_LogF1(level, stdout, fmt, arg1)
#define IMK_Log2(level, fmt, arg1, arg2)                                     IMK_LogF2(level, stdout, fmt, arg1, arg2)
#define IMK_Log3(level, fmt, arg1, arg2, arg3)                               IMK_LogF3(level, stdout, fmt, arg1, arg2, arg3)
#define IMK_Log4(level, fmt, arg1, arg2, arg3, arg4)                         IMK_LogF4(level, stdout, fmt, arg1, arg2, arg3, arg4)
#define IMK_Log5(level, fmt, arg1, arg2, arg3, arg4, arg5)                   IMK_LogF5(level, stdout, fmt, arg1, arg2, arg3, arg4, arg5)
#define IMK_Log6(level, fmt, arg1, arg2, arg3, arg4, arg5, arg6)             IMK_LogF6(level, stdout, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define IMK_Log7(level, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7)       IMK_LogF7(level, stdout, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7)
#define IMK_Log8(level, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) IMK_LogF8(level, stdout, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
/* clang-format on */

enum {
  IMK_LOG_TRACE,
  IMK_LOG_DEBUG,
  IMK_LOG_INFO,
  IMK_LOG_WARN,
  IMK_LOG_ERROR,
  IMK_LOG_FATAL
};
enum {
  IMK_LOG_MASK_TRACE = (1 << IMK_LOG_TRACE),
  IMK_LOG_MASK_DEBUG = (1 << IMK_LOG_DEBUG),
  IMK_LOG_MASK_INFO = (1 << IMK_LOG_INFO),
  IMK_LOG_MASK_WARN = (1 << IMK_LOG_WARN),
  IMK_LOG_MASK_ERROR = (1 << IMK_LOG_ERROR),
  IMK_LOG_MASK_FATAL = (1 << IMK_LOG_FATAL)
};

#define IMK_LOG_MASK_NONE 0
#define IMK_LOG_MASK_ALL                                                       \
  (IMK_LOG_MASK_TRACE | IMK_LOG_MASK_DEBUG | IMK_LOG_MASK_INFO |               \
   IMK_LOG_MASK_WARN | IMK_LOG_MASK_ERROR | IMK_LOG_MASK_FATAL)

void IMK_LogVFBW(u8 level, FILE *fp, char const *file, int line,
                 char const *fmt, va_list args);
void IMK_LogVBW(u8 level, char const *file, int line, char const *fmt,
                va_list args);
void IMK_LogFBW(u8 level, FILE *fp, char const *file, int line, char const *fmt,
                ...);
void IMK_LogBW(u8 level, char const *file, int line, char const *fmt, ...);

void IMK_LogVFCol(u8 level, FILE *fp, char const *file, int line,
                  char const *fmt, va_list args);
void IMK_LogVCol(u8 level, char const *file, int line, char const *fmt,
                 va_list args);
void IMK_LogFCol(u8 level, FILE *fp, char const *file, int line,
                 char const *fmt, ...);
void IMK_LogCol(u8 level, char const *file, int line, char const *fmt, ...);

void IMK_LogSetMask(u8 levelmsk);
void IMK_LogSetMin(u8 level);
u8 IMK_LogGetMask(void);
void IMK_LogAddMask(u8 levelmsk);
void IMK_LogClearMask(u8 levelmsk);

#ifdef USING_NAMESPACE_IMK_LOG
#define LogF IMK_LogF
#define LogF1 IMK_LogF1
#define LogF2 IMK_LogF2
#define LogF3 IMK_LogF3
#define LogF4 IMK_LogF4
#define LogF5 IMK_LogF5
#define LogF6 IMK_LogF6
#define LogF7 IMK_LogF7
#define LogF8 IMK_LogF8

#define Log IMK_Log
#define Log1 IMK_Log1
#define Log2 IMK_Log2
#define Log3 IMK_Log3
#define Log4 IMK_Log4
#define Log5 IMK_Log5
#define Log6 IMK_Log6
#define Log7 IMK_Log7
#define Log8 IMK_Log8

#define LOG_TRACE IMK_LOG_TRACE
#define LOG_DEBUG IMK_LOG_DEBUG
#define LOG_INFO IMK_LOG_INFO
#define LOG_WARN IMK_LOG_WARN
#define LOG_ERROR IMK_LOG_ERROR
#define LOG_FATAL IMK_LOG_FATAL

#define LOG_MASK_TRACE IMK_LOG_MASK_TRACE
#define LOG_MASK_DEBUG IMK_LOG_MASK_DEBUG
#define LOG_MASK_INFO IMK_LOG_MASK_INFO
#define LOG_MASK_WARN IMK_LOG_MASK_WARN
#define LOG_MASK_ERROR IMK_LOG_MASK_ERROR
#define LOG_MASK_FATAL IMK_LOG_MASK_FATAL
#define LOG_MASK_NONE IMK_LOG_MASK_NONE
#define LOG_MASK_ALL IMK_LOG_MASK_ALL

#define LogVFBW IMK_LogVFBW
#define LogVBW IMK_LogVBW
#define LogFBW IMK_LogFBW
#define LogBW IMK_LogBW

#define LogVFCol IMK_LogVFCol
#define LogVCol IMK_LogVCol
#define LogFCol IMK_LogFCol
#define LogCol IMK_LogCol

#define LogSetMask IMK_LogSetMask
#define LogSetMin IMK_LogSetMin
#define LogGetMask IMK_LogGetMask
#define LogAddMask IMK_LogGetMask
#define LogClearMask IMK_LogClearMask

#endif /* USING_NAMESPACE_IMK_LOG */

#endif /* !IMK_LOG_H_UEK2076US6EIQ8Q7 */
