#ifndef IMKLIB_IO_IMK_PRINTF_H_
#define IMKLIB_IO_IMK_PRINTF_H_

#include <stdarg.h>
#include <stdio.h>

int IMK_SNPrintf(char *str, size_t size, char const *fmt, ...);
int IMK_VSNPrintf(char *str, size_t size, char const *fmt, va_list ap);

#ifdef USING_IMKLIB_IO_IMK_PRINTF_H_
#define SNPrintf  IMK_SNPrintf
#define VSNPrintf IMK_VSNPrintf
#endif /* USING_IMKLIB_IO_IMK_PRINTF_H_ */

#endif /* !IMKLIB_IO_IMK_PRINTF_H_ */

