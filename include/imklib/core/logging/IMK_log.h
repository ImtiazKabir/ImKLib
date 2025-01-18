#ifndef IMK_LOG_H_UEK2076US6EIQ8Q7
#define IMK_LOG_H_UEK2076US6EIQ8Q7

#include <stdarg.h>
#include <stdio.h>

#include "IMK_index_ref.slug"
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
#include "IMK_index_ref.slug"
#include SLUG_IMK_ATTACH_LOG
#endif /* USING_NAMESPACE_IMK_LOG */

#endif /* !IMK_LOG_H_UEK2076US6EIQ8Q7 */
