#ifndef IMKLIB_IO_IMK_PRINTF_H_
#define IMKLIB_IO_IMK_PRINTF_H_

#include <stdarg.h>
#include <stdio.h>

int IMK_SNPrintF(char *str, size_t size, char const *fmt, ...);
int IMK_VSNPrintF(char *str, size_t size, char const *fmt, va_list ap);

#ifdef USING_IMKLIB_IO_IMK_PRINTF_H_
#define SNPrintF  IMK_SNPrintF
#define VSNPrintF IMK_VSNPrintF
#endif /* USING_IMKLIB_IO_IMK_PRINTF_H_ */

#endif /* !IMKLIB_IO_IMK_PRINTF_H_ */

