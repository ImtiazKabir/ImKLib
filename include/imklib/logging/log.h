#ifndef IMKLIB_LOGGING_LOG_H_
#define IMKLIB_LOGGING_LOG_H_

#include <stdarg.h>
#include <stdio.h>

/* clang-format off */
#define IMK_Logf(level, fp, fmt)                                                  IMK_LogfCol(level, fp, __FILE__, __LINE__, fmt)
#define IMK_Logf1(level, fp, fmt, arg1)                                           IMK_LogfCol(level, fp, __FILE__, __LINE__, fmt, arg1)
#define IMK_Logf2(level, fp, fmt, arg1, arg2)                                     IMK_LogfCol(level, fp, __FILE__, __LINE__, fmt, arg1, arg2)
#define IMK_Logf3(level, fp, fmt, arg1, arg2, arg3)                               IMK_LogfCol(level, fp, __FILE__, __LINE__, fmt, arg1, arg2, arg3)
#define IMK_Logf4(level, fp, fmt, arg1, arg2, arg3, arg4)                         IMK_LogfCol(level, fp, __FILE__, __LINE__, fmt, arg1, arg2, arg3, arg4)
#define IMK_Logf5(level, fp, fmt, arg1, arg2, arg3, arg4, arg5)                   IMK_LogfCol(level, fp, __FILE__, __LINE__, fmt, arg1, arg2, arg3, arg4, arg5)
#define IMK_Logf6(level, fp, fmt, arg1, arg2, arg3, arg4, arg5, arg6)             IMK_LogfCol(level, fp, __FILE__, __LINE__, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define IMK_Logf7(level, fp, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7)       IMK_LogfCol(level, fp, __FILE__, __LINE__, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7)
#define IMK_Logf8(level, fp, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) IMK_LogfCol(level, fp, __FILE__, __LINE__, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)

#define IMK_Log(level, fmt)                                                  IMK_Logf(level, stdout, fmt)
#define IMK_Log1(level, fmt, arg1)                                           IMK_Logf1(level, stdout, fmt, arg1)
#define IMK_Log2(level, fmt, arg1, arg2)                                     IMK_Logf2(level, stdout, fmt, arg1, arg2)
#define IMK_Log3(level, fmt, arg1, arg2, arg3)                               IMK_Logf3(level, stdout, fmt, arg1, arg2, arg3)
#define IMK_Log4(level, fmt, arg1, arg2, arg3, arg4)                         IMK_Logf4(level, stdout, fmt, arg1, arg2, arg3, arg4)
#define IMK_Log5(level, fmt, arg1, arg2, arg3, arg4, arg5)                   IMK_Logf5(level, stdout, fmt, arg1, arg2, arg3, arg4, arg5)
#define IMK_Log6(level, fmt, arg1, arg2, arg3, arg4, arg5, arg6)             IMK_Logf6(level, stdout, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define IMK_Log7(level, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7)       IMK_Logf7(level, stdout, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7)
#define IMK_Log8(level, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) IMK_Logf8(level, stdout, fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
/* clang-format on */

enum { IMK_LOG_TRACE, IMK_LOG_DEBUG, IMK_LOG_INFO, IMK_LOG_WARN, IMK_LOG_ERROR, IMK_LOG_FATAL };
enum {
  IMK_LOG_MASK_TRACE = (1 << IMK_LOG_TRACE),
  IMK_LOG_MASK_DEBUG = (1 << IMK_LOG_DEBUG),
  IMK_LOG_MASK_INFO = (1 << IMK_LOG_INFO),
  IMK_LOG_MASK_WARN = (1 << IMK_LOG_WARN),
  IMK_LOG_MASK_ERROR = (1 << IMK_LOG_ERROR),
  IMK_LOG_MASK_FATAL = (1 << IMK_LOG_FATAL)
};

#define IMK_LOG_MASK_NONE 0
#define IMK_LOG_MASK_ALL                                                               \
  (IMK_LOG_MASK_TRACE | IMK_LOG_MASK_DEBUG | IMK_LOG_MASK_INFO | IMK_LOG_MASK_WARN | IMK_LOG_MASK_ERROR | IMK_LOG_MASK_FATAL)

void IMK_LogvfBW(unsigned char level, FILE *fp, char const *file, int line,
               char const *fmt, va_list args);
void IMK_LogvBW(unsigned char level, char const *file, int line,
              char const *fmt, va_list args);
void IMK_LogfBW(unsigned char level, FILE *fp, char const *file, int line,
              char const *fmt, ...);
void IMK_LogBW(unsigned char level, char const *file, int line,
             char const *fmt, ...);

void IMK_LogvfCol(unsigned char level, FILE *fp, char const *file,
                int line, char const *fmt, va_list args);
void IMK_LogvCol(unsigned char level, char const *file, int line,
               char const *fmt, va_list args);
void IMK_LogfCol(unsigned char level, FILE *fp, char const *file, int line,
               char const *fmt, ...);
void IMK_LogCol(unsigned char level, char const *file, int line,
              char const *fmt, ...);

void IMK_LogSetMask(unsigned char levelmsk);
void IMK_LogSetMin(unsigned char level);
unsigned char IMK_LogGetMask(void);
void IMK_LogAddMask(unsigned char levelmsk);
void IMK_LogClearMask(unsigned char levelmsk);

#ifdef USING_IMKLIB_LOGGING_LOG
#define Logf      IMK_Logf
#define Logf1     IMK_Logf1
#define Logf2     IMK_Logf2
#define Logf3     IMK_Logf3
#define Logf4     IMK_Logf4
#define Logf5     IMK_Logf5
#define Logf6     IMK_Logf6
#define Logf7     IMK_Logf7
#define Logf8     IMK_Logf8

#define Log      IMK_Log
#define Log1     IMK_Log1
#define Log2     IMK_Log2
#define Log3     IMK_Log3
#define Log4     IMK_Log4
#define Log5     IMK_Log5
#define Log6     IMK_Log6
#define Log7     IMK_Log7
#define Log8     IMK_Log8

#define LOG_TRACE  IMK_LOG_TRACE
#define LOG_DEBUG  IMK_LOG_DEBUG
#define LOG_INFO   IMK_LOG_INFO 
#define LOG_WARN   IMK_LOG_WARN 
#define LOG_ERROR  IMK_LOG_ERROR
#define LOG_FATAL  IMK_LOG_FATAL

#define LOG_MASK_TRACE  IMK_LOG_MASK_TRACE
#define LOG_MASK_DEBUG  IMK_LOG_MASK_DEBUG
#define LOG_MASK_INFO   IMK_LOG_MASK_INFO
#define LOG_MASK_WARN   IMK_LOG_MASK_WARN
#define LOG_MASK_ERROR  IMK_LOG_MASK_ERROR
#define LOG_MASK_FATAL  IMK_LOG_MASK_FATAL
#define LOG_MASK_NONE   IMK_LOG_MASK_NONE
#define LOG_MASK_ALL    IMK_LOG_MASK_ALL

#endif /* USING_IMKLIB_LOGGING_LOG */

#endif /* !IMKLIB_LOGGING_LOG_H_ */

