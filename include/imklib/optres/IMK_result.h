#ifndef IMKLIB_OPTRES_IMK_RESULT_H_
#define IMKLIB_OPTRES_IMK_RESULT_H_

#include "../base/IMK_floats.h"
#include "../base/IMK_ints.h"
#include "../base/IMK_macros.h"
#include "../io/IMK_assert.h"

#define IMK_RESULT_OK(res) GLUE(res, _Ok)
#define IMK_RESULT_ERR(res) GLUE(res, _Err)
#define IMK_RESULT_IS_OK(res) GLUE(res, _IsOk)
#define IMK_RESULT_IS_ERR(res) GLUE(res, _IsErr)
#define IMK_RESULT_UNWRAP(res) GLUE(res, _Unwrap)
#define IMK_RESULT_EXPECT(res) GLUE(res, _Expect)
#define IMK_RESULT_UNWRAP_OR(res) GLUE(res, _UnwrapOr)
#define IMK_RESULT_UNWRAP_ERR(res) GLUE(res, _UnwrapErr)

#ifdef USING_IMKLIB_OPTRES_IMK_RESULT
#endif /* USING_IMKLIB_OPTRES_IMK_RESULT */

#endif /* !IMKLIB_OPTRES_IMK_RESULT_H_ */
