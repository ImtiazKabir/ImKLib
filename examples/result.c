#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#define USING_NAMESPACE_IMK_CORE
#include SLUG_IMK_HEADER_CORE

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

ERROR_DECLARE(IllegalArgument, Error)
ERROR_DECLARE(TooLargeArgument, IllegalArgument)
ERROR_DECLARE(OutOfDomainArgument, IllegalArgument)

ERROR_DEFINE(IllegalArgument, Error, -1, "Illegal argument")
ERROR_DEFINE(TooLargeArgument, IllegalArgument, -2, "Too large argument")
ERROR_DEFINE(OutOfDomainArgument, IllegalArgument, -3, "Out of domain argument")

static ResInt factorial2(int n) {
  if (n < 0) {
    return ResInt_Err(KlassAllocP(OutOfDomainArgumentKlass, NULL, FORCE_HEAP,
                                  U32(3), PARAM_RPTR,
                                  "Negative numbers passed to factorial",
                                  PARAM_RPTR, NULL, PARAM_U32, FORCE_HEAP));
  }
  if (n >= 20) {
    return ResInt_Err(
        KlassAllocP(TooLargeArgumentKlass, NULL, FORCE_HEAP, U32(3), PARAM_RPTR,
                    "Numbers greater than 19 cant be processed with the "
                    "current implementation of factorial",
                    PARAM_RPTR, NULL, PARAM_U32, FORCE_HEAP));
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
  int n = -20;
  ResInt res = factorial2(n);
  if (ResInt_IsErr(res)) {
    Ptr err = ResInt_UnwrapErr(res);
    if (IsOf(err, TooLargeArgumentKlass)) {
      Log(LOG_WARN, "Too large argument, gracefully exiting");
      Drop(&err);
      return 0;
    } else {
      ErrorThrow(err, NULL, FORCE_HEAP);
    }
  } else {
    int fact = ResInt_Unwrap(factorial2(n));
    Log2(LOG_INFO, "%d! = %d", n, fact);
  }
  return 0;
}
