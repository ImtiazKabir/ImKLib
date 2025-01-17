#ifndef IMK_INTS_H_1YUBCT7UJQO2X8HS
#define IMK_INTS_H_1YUBCT7UJQO2X8HS

#include <limits.h>

/* Define 8-bit integer types */
#if CHAR_BIT == 8
typedef signed char s8;
typedef unsigned char u8;
#define S8_MIN SCHAR_MIN
#define S8_MAX SCHAR_MAX
#define U8_MAX UCHAR_MAX
#define S8_FMT "d"
#define U8_FMT "u"
#define S8(value) ((s8)(value))
#define U8(value) ((u8)(value))
#else
#error "8-bit type not supported on this platform"
#endif

/* Define 16-bit integer types */
#if SHRT_MAX == 32767
typedef short s16;
typedef unsigned short u16;
#define S16_MIN SHRT_MIN
#define S16_MAX SHRT_MAX
#define U16_MAX USHRT_MAX
#define S16_FMT "hd"
#define U16_FMT "hu"
#define S16(value) ((s16)(value))
#define U16(value) ((u16)(value))
#elif INT_MAX == 32767
typedef int s16;
typedef unsigned int u16;
#define S16_MIN INT_MIN
#define S16_MAX INT_MAX
#define U16_MAX UINT_MAX
#define S16_FMT "d"
#define U16_FMT "u"
#define S16(value) ((s16)(value))
#define U16(value) ((u16)(value))
#else
#error "16-bit type not supported on this platform"
#endif

/* Define 32-bit integer types */
#if INT_MAX == 2147483647
typedef int s32;
typedef unsigned int u32;
#define S32_MIN INT_MIN
#define S32_MAX INT_MAX
#define U32_MAX UINT_MAX
#define S32_FMT "d"
#define U32_FMT "u"
#define S32(value) ((s32)(value))
#define U32(value) ((u32)(value))
#elif LONG_MAX == 2147483647
typedef long s32;
typedef unsigned long u32;
#define S32_MIN LONG_MIN
#define S32_MAX LONG_MAX
#define U32_MAX ULONG_MAX
#define S32_FMT "ld"
#define U32_FMT "lu"
#define S32(value) ((s32)(value))
#define U32(value) ((u32)(value))
#else
#error "32-bit type not supported on this platform"
#endif

/* Define 64-bit integer types (if available) */
/*#if defined(LLONG_MAX) && LLONG_MAX == 9223372036854775807*/
/*typedef long long s64;*/
/*typedef unsigned long long u64;*/
/*#define S64_MIN LLONG_MIN*/
/*#define S64_MAX LLONG_MAX*/
/*#define U64_MAX ULLONG_MAX*/
/*#define S64_FMT "lld"*/
/*#define U64_FMT "llu"*/
/*#define S64(value) ((s64)(value##LL))*/
/*#define U64(value) ((u64)(value##ULL))*/
#if defined(LONG_MAX) && LONG_MAX == 9223372036854775807
typedef long s64;
typedef unsigned long u64;
#define S64_MIN LONG_MIN
#define S64_MAX LONG_MAX
#define U64_MAX ULONG_MAX
#define S64_FMT "ld"
#define U64_FMT "lu"
#define S64(value) ((s64)(value##L))
#define U64(value) ((u64)(value##UL))
#else
/* If your platform doesn't support 64-bit integers, comment out the next line
 */
#error "64-bit type not supported on this platform"
#endif

#endif /* !IMK_INTS_H_1YUBCT7UJQO2X8HS */
