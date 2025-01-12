#define USING_IMKLIB_LOGGING_IMK_LOG
#define USING_IMKLIB_CORE_IMK_PTR
#include "imklib/core/IMK_ptr.h"
#include "imklib/logging/IMK_log.h"
#include "imklib/optres/IMK_result.h"

IMK_RESULT_DECLARE(ResultNum, int, char const *)
typedef struct ResultNum ResultNum;

static Ptr StrError(char const *err) {
  (void)err;
  return PtrBorrowRaw((void *)err, PTR_STATIC);
}

IMK_RESULT_DEFINE(ResultNum, int, char const *, StrError, NULL)

static ResultNum factorial(int n) {
  if (n < 0) {
    return ResultNum_Err("Illegal argument: Negative number");
  }
  if (n >= 20) {
    return ResultNum_Err("Illegal argument: Too large number");
  }
  if (n == 0) {
    return ResultNum_Ok(1);
  }
  {
    int subproblem;
    IMK_RESULT_TRY_OR(subproblem, ResultNum, factorial(n - 1), ResultNum);
    return ResultNum_Ok(n * subproblem);
  }
}

int main(void) {
  int n = 20;
  int fact = ResultNum_Unwrap(factorial(n));
  Log2(LOG_INFO, "%d! = %d", n, fact);
  return 0;
}
