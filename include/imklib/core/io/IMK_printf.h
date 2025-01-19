#ifndef IMK_PRINTF_H_ZN244WV6EGPVSVIL
#define IMK_PRINTF_H_ZN244WV6EGPVSVIL

#include <stdarg.h>
#include <stdio.h>

int IMK_PrintF(char const *fmt, ...);
int IMK_FPrintF(FILE *stream, char const *fmt, ...);
int IMK_SPrintF(char *str, char const *fmt, ...);
int IMK_SNPrintF(char *str, size_t size, char const *fmt, ...);

int IMK_VPrintF(char const *fmt, va_list ap);
int IMK_VFPrintF(FILE *stream, char const *fmt, va_list ap);
int IMK_VSPrintF(char *str, char const *fmt, va_list ap);
int IMK_VSNPrintF(char *str, size_t size, char const *fmt, va_list ap);

#ifdef USING_NAMESPACE_IMK_PRINTF
#include "IMK_index_ref.slug"
#include SLUG_IMK_ATTACH_PRINTF
#endif /* USING_NAMESPACE_IMK_PRINTF */

#endif /* !IMK_PRINTF_H_ZN244WV6EGPVSVIL */
