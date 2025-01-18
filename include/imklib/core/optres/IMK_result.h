#ifndef IMK_RESULT_H_7CV443ZQWRBXXAKP
#define IMK_RESULT_H_7CV443ZQWRBXXAKP

#include <stddef.h>

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_BASE

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_PTR

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_ASSERT

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_PRINTF

#define IMK_RESULT_OK(res) GLUE(res, _Ok)
#define IMK_RESULT_ERR(res) GLUE(res, _Err)
#define IMK_RESULT_ERRC(res) GLUE(res, _ErrWithCode)
#define IMK_RESULT_IS_OK(res) GLUE(res, _IsOk)
#define IMK_RESULT_IS_ERR(res) GLUE(res, _IsErr)
#define IMK_RESULT_UNWRAP(res) GLUE(res, _Unwrap)
#define IMK_RESULT_EXPECT(res) GLUE(res, _Expect)
#define IMK_RESULT_UNWRAP_OR(res) GLUE(res, _UnwrapOr)
#define IMK_RESULT_UNWRAP_ERR(res) GLUE(res, _UnwrapErr)

#define IMK_RESULT_DECLARE(R, T, E)                                            \
  struct R {                                                                   \
    int err_code;                                                              \
    union {                                                                    \
      T ok_val;                                                                \
      E err_val;                                                               \
    } val;                                                                     \
  };                                                                           \
  struct R IMK_RESULT_OK(R)(T);                                                \
  struct R IMK_RESULT_ERR(R)(E);                                               \
  struct R IMK_RESULT_ERRC(R)(E, int);                                         \
  int IMK_RESULT_IS_OK(R)(struct R);                                           \
  int IMK_RESULT_IS_ERR(R)(struct R);                                          \
  T IMK_RESULT_UNWRAP(R)(struct R);                                            \
  T IMK_RESULT_EXPECT(R)(struct R, char const *);                              \
  T IMK_RESULT_UNWRAP_OR(R)(struct R, T);                                      \
  E IMK_RESULT_UNWRAP_ERR(R)(struct R);

#define IMK_RESULT_DEFINE(R, T, E, serr, ferr)                                 \
  struct R IMK_RESULT_OK(R)(T ok_val) {                                        \
    struct R res;                                                              \
    res.err_code = 0;                                                          \
    res.val.ok_val = ok_val;                                                   \
    return res;                                                                \
  }                                                                            \
  struct R IMK_RESULT_ERR(R)(E err_val) {                                      \
    struct R res;                                                              \
    res.err_code = -1;                                                         \
    res.val.err_val = err_val;                                                 \
    return res;                                                                \
  }                                                                            \
  struct R IMK_RESULT_ERRC(R)(E err_val, int err_code) {                       \
    struct R res;                                                              \
    res.err_code = err_code;                                                   \
    res.val.err_val = err_val;                                                 \
    return res;                                                                \
  }                                                                            \
  int IMK_RESULT_IS_OK(R)(struct R res) { return res.err_code == 0; }          \
  int IMK_RESULT_IS_ERR(R)(struct R res) { return res.err_code != 0; }         \
  T IMK_RESULT_UNWRAP(R)(struct R res) {                                       \
    if (IMK_RESULT_IS_ERR(R)(res)) {                                           \
      IMK_Ptr (*str_err)(E) = serr;                                            \
      if (str_err != NULL) {                                                   \
        char str[512] = {0};                                                   \
        IMK_Ptr s = str_err(res.val.err_val);                                  \
        IMK_SNPrintF(str, sizeof(str),                                         \
                     "Attempted to unwrap empty Result of type " #R            \
                     ". Instead had error: %s",                                \
                     (char *)(s.raw));                                         \
        IMK_Drop(&s);                                                          \
        IMK_PanicBox(str);                                                     \
      }                                                                        \
      IMK_PanicBox("Attempted to unwrap empty Result of type " #R              \
                   ". Instead had error");                                     \
    }                                                                          \
    return res.val.ok_val;                                                     \
  }                                                                            \
  T IMK_RESULT_EXPECT(R)(struct R res, char const *message_on_error) {         \
    IMK_ASSERT_MSG(IMK_RESULT_IS_OK(R)(res), message_on_error);                \
    return res.val.ok_val;                                                     \
  }                                                                            \
  T IMK_RESULT_UNWRAP_OR(R)(struct R res, T else_val) {                        \
    if (IMK_RESULT_IS_ERR(R)(res)) {                                           \
      void (*free_err)(E) = ferr;                                              \
      if (free_err != NULL) {                                                  \
        free_err(res.val.err_val);                                             \
      }                                                                        \
      return else_val;                                                         \
    }                                                                          \
    return res.val.ok_val;                                                     \
  }                                                                            \
  E IMK_RESULT_UNWRAP_ERR(R)(struct R res) {                                   \
    IMK_ASSERT_MSG(IMK_RESULT_IS_ERR(R)(res),                                  \
                   "Attempted to unwrap OK Result of type " #T " for error."); \
    return res.val.err_val;                                                    \
  }

#define IMK_RESULT_TRY(R, res, RET)                                            \
  do {                                                                         \
    R UNIQUE_NAME(GLUE(GLUE(result_, R), _try_at)) = res;                      \
    if (UNIQUE_NAME(GLUE(GLUE(result_, R), _try_at)).err_code != 0) {          \
      return IMK_RESULT_ERRC(RET)(res.val.err_val, res.err_code);              \
    }                                                                          \
  } while (0)

#define IMK_RESULT_TRY_OR(dest, R, res, RET)                                   \
  do {                                                                         \
    R UNIQUE_NAME(GLUE(GLUE(result_, R), _try_at)) = res;                      \
    if (UNIQUE_NAME(GLUE(GLUE(result_, R), _try_at)).err_code != 0) {          \
      return IMK_RESULT_ERRC(RET)(res.val.err_val, res.err_code);              \
    }                                                                          \
    dest = UNIQUE_NAME(GLUE(GLUE(result_, R), _try_at)).val.ok_val;            \
  } while (0)

IMK_RESULT_DECLARE(IMK_ResVoid, int, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResInt, int, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResShort, short, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResLong, long, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResFloat, float, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResDouble, double, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResChar, char, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResUInt, unsigned int, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResUShort, unsigned short, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResULong, unsigned long, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResUChar, unsigned char, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResRPtr, void *, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResPtr, IMK_Ptr, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResS8, s8, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResS16, s16, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResS32, s32, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResS64, s64, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResU8, u8, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResU16, u16, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResU32, u32, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResU64, u64, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResF32, f32, IMK_Ptr)
IMK_RESULT_DECLARE(IMK_ResF64, f64, IMK_Ptr)

typedef struct IMK_ResVoid IMK_ResVoid;
typedef struct IMK_ResInt IMK_ResInt;
typedef struct IMK_ResShort IMK_ResShort;
typedef struct IMK_ResLong IMK_ResLong;
typedef struct IMK_ResFloat IMK_ResFloat;
typedef struct IMK_ResDouble IMK_ResDouble;
typedef struct IMK_ResChar IMK_ResChar;
typedef struct IMK_ResUInt IMK_ResUInt;
typedef struct IMK_ResUShort IMK_ResUShort;
typedef struct IMK_ResULong IMK_ResULong;
typedef struct IMK_ResUChar IMK_ResUChar;
typedef struct IMK_ResPtr IMK_ResPtr;
typedef struct IMK_ResRPtr IMK_ResRPtr;
typedef struct IMK_ResS8 IMK_ResS8;
typedef struct IMK_ResS16 IMK_ResS16;
typedef struct IMK_ResS32 IMK_ResS32;
typedef struct IMK_ResS64 IMK_ResS64;
typedef struct IMK_ResU8 IMK_ResU8;
typedef struct IMK_ResU16 IMK_ResU16;
typedef struct IMK_ResU32 IMK_ResU32;
typedef struct IMK_ResU64 IMK_ResU64;
typedef struct IMK_ResF32 IMK_ResF32;
typedef struct IMK_ResF64 IMK_ResF64;

#ifdef USING_NAMESPACE_IMK_RESULT
#include "IMK_index_ref.slug"
#include SLUG_IMK_ATTACH_RESULT
#endif /* USING_NAMESPACE_IMK_RESULT */

#endif /* !IMK_RESULT_H_7CV443ZQWRBXXAKP */
