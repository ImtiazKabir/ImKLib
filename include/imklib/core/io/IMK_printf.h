#ifndef IMK_PRINTF_H_ZN244WV6EGPVSVIL
#define IMK_PRINTF_H_ZN244WV6EGPVSVIL

#include <stdarg.h>
#include <stdio.h>

int IMK_SNPrintF(char *str, size_t size, char const *fmt, ...);
int IMK_VSNPrintF(char *str, size_t size, char const *fmt, va_list ap);

#ifdef USING_NAMESPACE_IMK_PRINTF_H_
#define SNPrintF IMK_SNPrintF
#define VSNPrintF IMK_VSNPrintF
#endif /* USING_NAMESPACE_IMK_PRINTF_H_ */

#endif /* !IMK_PRINTF_H_ZN244WV6EGPVSVIL */
