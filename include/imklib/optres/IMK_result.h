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

#ifdef USING_IMKLIB_OPTRES_IMK_RESULT
#endif /* USING_IMKLIB_OPTRES_IMK_RESULT */

#endif /* !IMKLIB_OPTRES_IMK_RESULT_H_ */
