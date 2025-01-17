#ifndef IMKLIB_BASE_IMK_MACROS_H_
#define IMKLIB_BASE_IMK_MACROS_H_

#include "IMK_slug_index_ref.h"
#include IMK_SLUG_INTS

#define STRINGIFY_(S) #S
#define STRINGIFY(S) STRINGIFY_(S)
#define GLUE_(A, B) A##B
#define GLUE(A, B) GLUE_(A, B)

#define UNIQUE_NAME(t) GLUE(t, __LINE__)

#define STATIC_ASSERT(c, l) typedef u8 UNIQUE_NAME(l)[(c) ? 1 : -1]

#define STATEMENT(S)                                                           \
  do {                                                                         \
    S                                                                          \
  } while (0)

#if !defined(PROGRAM_CRASH)
#define PROGRAM_CRASH() (*(volatile int *)0 = 0)
#endif

#ifdef ENABLE_CRASSERT
#define CRASSERT(c) STATEMENT(if (!(c)) { PROGRAM_CRASH(); })
#else
#define CRASSERT(c)
#endif /* ENABLE_CRASSERT */

#define ARRAY_COUNT(a) (sizeof(a) / sizeof(a[0]))

#define IMPLIES(a, b) (!(a) || (b))

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define CLAMP(a, x, b) (((x) < (a)) ? (a) : ((b) < (x)) ? (b) : (x))

#define REINTERPRET_CAST(type, value) *(type *)&value

#define FOR(D, S, B)                                                           \
  {                                                                            \
    D;                                                                         \
    for (S)                                                                    \
      B                                                                        \
  }

#define BIN1(b0) U64(b0)

#define BIN2(b1, b0) ((BIN1(b1) << 1) | BIN1(b0))

#define BIN4(b3, b2, b1, b0) ((BIN2(b3, b2) << 2) | BIN2(b1, b0))

#define BIN8(b7, b6, b5, b4, b3, b2, b1, b0)                                   \
  ((BIN4(b7, b6, b5, b4) << 4) | BIN4(b3, b2, b1, b0))

#define BIN16(b15, b14, b13, b12, b11, b10, b9, b8, b7, b6, b5, b4, b3, b2,    \
              b1, b0)                                                          \
  ((BIN8(b15, b14, b13, b12, b11, b10, b9, b8) << 8) |                         \
   BIN8(b7, b6, b5, b4, b3, b2, b1, b0))

#define BIN32(b31, b30, b29, b28, b27, b26, b25, b24, b23, b22, b21, b20, b19, \
              b18, b17, b16, b15, b14, b13, b12, b11, b10, b9, b8, b7, b6, b5, \
              b4, b3, b2, b1, b0)                                              \
  ((BIN16(b31, b30, b29, b28, b27, b26, b25, b24, b23, b22, b21, b20, b19,     \
          b18, b17, b16)                                                       \
    << 16) |                                                                   \
   BIN16(b15, b14, b13, b12, b11, b10, b9, b8, b7, b6, b5, b4, b3, b2, b1,     \
         b0))

#define BIN64(b63, b62, b61, b60, b59, b58, b57, b56, b55, b54, b53, b52, b51, \
              b50, b49, b48, b47, b46, b45, b44, b43, b42, b41, b40, b39, b38, \
              b37, b36, b35, b34, b33, b32, b31, b30, b29, b28, b27, b26, b25, \
              b24, b23, b22, b21, b20, b19, b18, b17, b16, b15, b14, b13, b12, \
              b11, b10, b9, b8, b7, b6, b5, b4, b3, b2, b1, b0)                \
  ((BIN32(b63, b62, b61, b60, b59, b58, b57, b56, b55, b54, b53, b52, b51,     \
          b50, b49, b48, b47, b46, b45, b44, b43, b42, b41, b40, b39, b38,     \
          b37, b36, b35, b34, b33, b32)                                        \
    << 32) |                                                                   \
   BIN32(b31, b30, b29, b28, b27, b26, b25, b24, b23, b22, b21, b20, b19, b18, \
         b17, b16, b15, b14, b13, b12, b11, b10, b9, b8, b7, b6, b5, b4, b3,   \
         b2, b1, b0))

#endif /* !IMKLIB_BASE_IMK_MACROS_H_ */
