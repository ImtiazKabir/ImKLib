#define USING_IMKLIB_LOGGING_IMK_LOG
#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_OPTRES_IMK_RESULT
#include "imklib/core/IMK_ptr.h"
#include "imklib/logging/IMK_log.h"
#include "imklib/optres/IMK_result.h"

RESULT_DECLARE(ResultNum, int, char const *)
typedef struct ResultNum ResultNum;

static Ptr StrError(char const *err) {
  Ptr ptr = PtrOwnRaw((void *)err, PTR_STATIC);
  PtrSetRdOnly(&ptr);
  return PtrMove(&ptr);
}

RESULT_DEFINE(ResultNum, int, char const *, StrError, NULL)

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
    RESULT_TRY_OR(subproblem, ResultNum, factorial(n - 1), ResultNum);
    return ResultNum_Ok(n * subproblem);
  }
}

static ResInt factorial2(int n) {
  if (n < 0) {
    return ResInt_Err(
        PtrOwnRaw((void *)"Illegal argument: Negative number", PTR_STATIC));
  }
  if (n >= 20) {
    return ResInt_Err(
        PtrOwnRaw((void *)"Illegal argument: Too large number", PTR_STATIC));
  }
  if (n == 0) {
    return ResInt_Ok(1);
  }
  {
    int subproblem;
    RESULT_TRY_OR(subproblem, ResInt, factorial2(n - 1), ResInt);
    return ResInt_Ok(n * subproblem);
  }
}

int main(void) {
  int n = 20;
  /*int fact = ResultNum_Unwrap(factorial(n));*/
  int fact = ResInt_Unwrap(factorial2(n));
  Log2(LOG_INFO, "%d! = %d", n, fact);
  return 0;
}
