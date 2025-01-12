#ifndef IMKLIB_OPTRES_IMK_RESULT_H_
#define IMKLIB_OPTRES_IMK_RESULT_H_

#include <stddef.h>

#include "../base/IMK_floats.h"
#include "../base/IMK_ints.h"
#include "../base/IMK_macros.h"
#include "../core/IMK_ptr.h"
#include "../io/IMK_assert.h"
#include "../io/IMK_printf.h"

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
        char str[128] = {0};                                                   \
        IMK_Ptr s = str_err(res.val.err_val);                                  \
        IMK_SNPrintF(str, sizeof(str),                                         \
                     "Attempted to unwrap empty Result of type " #R            \
                     ". Instead had error: %s",                                \
                     (char *)(s.raw));                                         \
        IMK_PtrDrop(&s);                                                       \
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
      return IMK_RESULT_ERRC(RET)(res.val.err_val, err_code);                  \
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
IMK_RESULT_DECLARE(IMK_ResPtr, void *, IMK_Ptr)
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

#ifdef USING_IMKLIB_OPTRES_IMK_RESULT
#define RESULT_OK IMK_RESULT_OK
#define RESULT_ERR IMK_RESULT_ERR
#define RESULT_ERRC IMK_RESULT_ERRC
#define RESULT_IS_OK IMK_RESULT_IS_OK
#define RESULT_IS_ERR IMK_RESULT_IS_ERR
#define RESULT_UNWRAP IMK_RESULT_UNWRAP
#define RESULT_EXPECT IMK_RESULT_EXPECT
#define RESULT_UNWRAP_OR IMK_RESULT_UNWRAP_OR
#define RESULT_TRY IMK_RESULT_TRY
#define RESULT_TRY_OR IMK_RESULT_TRY_OR

#define RESULT_DECLARE IMK_RESULT_DECLARE
#define RESULT_DEFINE IMK_RESULT_DEFINE

typedef IMK_ResVoid ResVoid;
typedef IMK_ResInt ResInt;
typedef IMK_ResShort ResShort;
typedef IMK_ResLong ResLong;
typedef IMK_ResFloat ResFloat;
typedef IMK_ResDouble ResDouble;
typedef IMK_ResChar ResChar;
typedef IMK_ResUInt ResUInt;
typedef IMK_ResUShort ResUShort;
typedef IMK_ResULong ResULong;
typedef IMK_ResUChar ResUChar;
typedef IMK_ResPtr ResPtr;
typedef IMK_ResS8 ResS8;
typedef IMK_ResS16 ResS16;
typedef IMK_ResS32 ResS32;
typedef IMK_ResS64 ResS64;
typedef IMK_ResU8 ResU8;
typedef IMK_ResU16 ResU16;
typedef IMK_ResU32 ResU32;
typedef IMK_ResU64 ResU64;
typedef IMK_ResF32 ResF32;
typedef IMK_ResF64 ResF64;

#define ResVoid_Ok IMK_ResVoid_Ok
#define ResVoid_Err IMK_ResVoid_Err
#define ResVoid_ErrWithCode IMK_ResVoid_ErrWithCode
#define ResVoid_IsOk IMK_ResVoid_IsOk
#define ResVoid_IsErr IMK_ResVoid_IsErr
#define ResVoid_Unwrap IMK_ResVoid_Unwrap
#define ResVoid_Expect IMK_ResVoid_Expect
#define ResVoid_UnwrapOr IMK_ResVoid_UnwrapOr

#define ResInt_Ok IMK_ResInt_Ok
#define ResInt_Err IMK_ResInt_Err
#define ResInt_ErrWithCode IMK_ResInt_ErrWithCode
#define ResInt_IsOk IMK_ResInt_IsOk
#define ResInt_IsErr IMK_ResInt_IsErr
#define ResInt_Unwrap IMK_ResInt_Unwrap
#define ResInt_Expect IMK_ResInt_Expect
#define ResInt_UnwrapOr IMK_ResInt_UnwrapOr

#define ResShort_Ok IMK_ResShort_Ok
#define ResShort_Err IMK_ResShort_Err
#define ResShort_ErrWithCode IMK_ResShort_ErrWithCode
#define ResShort_IsOk IMK_ResShort_IsOk
#define ResShort_IsErr IMK_ResShort_IsErr
#define ResShort_Unwrap IMK_ResShort_Unwrap
#define ResShort_Expect IMK_ResShort_Expect
#define ResShort_UnwrapOr IMK_ResShort_UnwrapOr

#define ResLong_Ok IMK_ResLong_Ok
#define ResLong_Err IMK_ResLong_Err
#define ResLong_ErrWithCode IMK_ResLong_ErrWithCode
#define ResLong_IsOk IMK_ResLong_IsOk
#define ResLong_IsErr IMK_ResLong_IsErr
#define ResLong_Unwrap IMK_ResLong_Unwrap
#define ResLong_Expect IMK_ResLong_Expect
#define ResLong_UnwrapOr IMK_ResLong_UnwrapOr

#define ResFloat_Ok IMK_ResFloat_Ok
#define ResFloat_Err IMK_ResFloat_Err
#define ResShort_ErrWithCode IMK_ResShort_ErrWithCode
#define ResFloat_IsOk IMK_ResFloat_IsOk
#define ResFloat_IsErr IMK_ResFloat_IsErr
#define ResFloat_Unwrap IMK_ResFloat_Unwrap
#define ResFloat_Expect IMK_ResFloat_Expect
#define ResFloat_UnwrapOr IMK_ResFloat_UnwrapOr

#define ResDouble_Ok IMK_ResDouble_Ok
#define ResDouble_Err IMK_ResDouble_Err
#define ResDouble_ErrWithCode IMK_ResDouble_ErrWithCode
#define ResDouble_IsOk IMK_ResDouble_IsOk
#define ResDouble_IsErr IMK_ResDouble_IsErr
#define ResDouble_Unwrap IMK_ResDouble_Unwrap
#define ResDouble_Expect IMK_ResDouble_Expect
#define ResDouble_UnwrapOr IMK_ResDouble_UnwrapOr

#define ResChar_Ok IMK_ResChar_Ok
#define ResChar_Err IMK_ResChar_Err
#define ResChar_ErrWithCode IMK_ResChar_ErrWithCode
#define ResChar_IsOk IMK_ResChar_IsOk
#define ResChar_IsErr IMK_ResChar_IsErr
#define ResChar_Unwrap IMK_ResChar_Unwrap
#define ResChar_Expect IMK_ResChar_Expect
#define ResChar_UnwrapOr IMK_ResChar_UnwrapOr

#define ResUInt_Ok IMK_ResUInt_Ok
#define ResUInt_Err IMK_ResUInt_Err
#define ResUInt_ErrWithCode IMK_ResUInt_ErrWithCode
#define ResUInt_IsOk IMK_ResUInt_IsOk
#define ResUInt_IsErr IMK_ResUInt_IsErr
#define ResUInt_Unwrap IMK_ResUInt_Unwrap
#define ResUInt_Expect IMK_ResUInt_Expect
#define ResUInt_UnwrapOr IMK_ResUInt_UnwrapOr

#define ResUShort_Ok IMK_ResUShort_Ok
#define ResUShort_Err IMK_ResUShort_Err
#define ResUShort_ErrWithCode IMK_ResUShort_ErrWithCode
#define ResUShort_IsOk IMK_ResUShort_IsOk
#define ResUShort_IsErr IMK_ResUShort_IsErr
#define ResUShort_Unwrap IMK_ResUShort_Unwrap
#define ResUShort_Expect IMK_ResUShort_Expect
#define ResUShort_UnwrapOr IMK_ResUShort_UnwrapOr

#define ResULong_Ok IMK_ResULong_Ok
#define ResULong_Err IMK_ResULong_Err
#define ResULong_ErrWithCode IMK_ResULong_ErrWithCode
#define ResULong_IsOk IMK_ResULong_IsOk
#define ResULong_IsErr IMK_ResULong_IsErr
#define ResULong_Unwrap IMK_ResULong_Unwrap
#define ResULong_Expect IMK_ResULong_Expect
#define ResULong_UnwrapOr IMK_ResULong_UnwrapOr

#define ResUChar_Ok IMK_ResUChar_Ok
#define ResUChar_Err IMK_ResUChar_Err
#define ResUChar_ErrWithCode IMK_ResUChar_ErrWithCode
#define ResUChar_IsOk IMK_ResUChar_IsOk
#define ResUChar_IsErr IMK_ResUChar_IsErr
#define ResUChar_Unwrap IMK_ResUChar_Unwrap
#define ResUChar_Expect IMK_ResUChar_Expect
#define ResUChar_UnwrapOr IMK_ResUChar_UnwrapOr

#define ResPtr_Ok IMK_ResPtr_Ok
#define ResPtr_Err IMK_ResPtr_Err
#define ResPtr_ErrWithCode IMK_ResPtr_ErrWithCode
#define ResPtr_IsOk IMK_ResPtr_IsOk
#define ResPtr_IsErr IMK_ResPtr_IsErr
#define ResPtr_Unwrap IMK_ResPtr_Unwrap
#define ResPtr_Expect IMK_ResPtr_Expect
#define ResPtr_UnwrapOr IMK_ResPtr_UnwrapOr

#define ResS8_Ok IMK_ResS8_Ok
#define ResS8_Err IMK_ResS8_Err
#define ResS8_ErrWithCode IMK_ResS8_ErrWithCode
#define ResS8_IsOk IMK_ResS8_IsOk
#define ResS8_IsErr IMK_ResS8_IsErr
#define ResS8_Unwrap IMK_ResS8_Unwrap
#define ResS8_Expect IMK_ResS8_Expect
#define ResS8_UnwrapOr IMK_ResS8_UnwrapOr

#define ResS16_Ok IMK_ResS16_Ok
#define ResS16_Err IMK_ResS16_Err
#define ResS16_ErrWithCode IMK_ResS16_ErrWithCode
#define ResS16_IsOk IMK_ResS16_IsOk
#define ResS16_IsErr IMK_ResS16_IsErr
#define ResS16_Unwrap IMK_ResS16_Unwrap
#define ResS16_Expect IMK_ResS16_Expect
#define ResS16_UnwrapOr IMK_ResS16_UnwrapOr

#define ResS32_Ok IMK_ResS32_Ok
#define ResS32_Err IMK_ResS32_Err
#define ResS32_ErrWithCode IMK_ResS32_ErrWithCode
#define ResS32_IsOk IMK_ResS32_IsOk
#define ResS32_IsErr IMK_ResS32_IsErr
#define ResS32_Unwrap IMK_ResS32_Unwrap
#define ResS32_Expect IMK_ResS32_Expect
#define ResS32_UnwrapOr IMK_ResS32_UnwrapOr

#define ResS64_Ok IMK_ResS64_Ok
#define ResS64_Err IMK_ResS64_Err
#define ResS64_ErrWithCode IMK_ResS64_ErrWithCode
#define ResS64_IsOk IMK_ResS64_IsOk
#define ResS64_IsErr IMK_ResS64_IsErr
#define ResS64_Unwrap IMK_ResS64_Unwrap
#define ResS64_Expect IMK_ResS64_Expect
#define ResS64_UnwrapOr IMK_ResS64_UnwrapOr

#define ResU8_Ok IMK_ResU8_Ok
#define ResU8_Err IMK_ResU8_Err
#define ResU8_ErrWithCode IMK_ResU8_ErrWithCode
#define ResU8_IsOk IMK_ResU8_IsOk
#define ResU8_IsErr IMK_ResU8_IsErr
#define ResU8_Unwrap IMK_ResU8_Unwrap
#define ResU8_Expect IMK_ResU8_Expect
#define ResU8_UnwrapOr IMK_ResU8_UnwrapOr

#define ResU16_Ok IMK_ResU16_Ok
#define ResU16_Err IMK_ResU16_Err
#define ResU16_ErrWithCode IMK_ResU16_ErrWithCode
#define ResU16_IsOk IMK_ResU16_IsOk
#define ResU16_IsErr IMK_ResU16_IsErr
#define ResU16_Unwrap IMK_ResU16_Unwrap
#define ResU16_Expect IMK_ResU16_Expect
#define ResU16_UnwrapOr IMK_ResU16_UnwrapOr

#define ResU32_Ok IMK_ResU32_Ok
#define ResU32_Err IMK_ResU32_Err
#define ResU32_ErrWithCode IMK_ResU32_ErrWithCode
#define ResU32_IsOk IMK_ResU32_IsOk
#define ResU32_IsErr IMK_ResU32_IsErr
#define ResU32_Unwrap IMK_ResU32_Unwrap
#define ResU32_Expect IMK_ResU32_Expect
#define ResU32_UnwrapOr IMK_ResU32_UnwrapOr

#define ResU64_Ok IMK_ResU64_Ok
#define ResU64_Err IMK_ResU64_Err
#define ResU64_ErrWithCode IMK_ResU64_ErrWithCode
#define ResU64_IsOk IMK_ResU64_IsOk
#define ResU64_IsErr IMK_ResU64_IsErr
#define ResU64_Unwrap IMK_ResU64_Unwrap
#define ResU64_Expect IMK_ResU64_Expect
#define ResU64_UnwrapOr IMK_ResU64_UnwrapOr

#define ResF32_Ok IMK_ResF32_Ok
#define ResF32_Err IMK_ResF32_Err
#define ResF32_ErrWithCode IMK_ResF32_ErrWithCode
#define ResF32_IsOk IMK_ResF32_IsOk
#define ResF32_IsErr IMK_ResF32_IsErr
#define ResF32_Unwrap IMK_ResF32_Unwrap
#define ResF32_Expect IMK_ResF32_Expect
#define ResF32_UnwrapOr IMK_ResF32_UnwrapOr

#define ResF64_Ok IMK_ResF64_Ok
#define ResF64_Err IMK_ResF64_Err
#define ResF64_ErrWithCode IMK_ResF64_ErrWithCode
#define ResF64_IsOk IMK_ResF64_IsOk
#define ResF64_IsErr IMK_ResF64_IsErr
#define ResF64_Unwrap IMK_ResF64_Unwrap
#define ResF64_Expect IMK_ResF64_Expect
#define ResF64_UnwrapOr IMK_ResF64_UnwrapOr
#endif /* USING_IMKLIB_OPTRES_IMK_RESULT */

#endif /* !IMKLIB_OPTRES_IMK_RESULT_H_ */
