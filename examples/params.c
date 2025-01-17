#define USING_IMKLIB_CORE_IMK_PARAMS
#define USING_IMKLIB_IO_IMK_ASSERT
#define USING_IMKLIB_LOGGING_IMK_LOG

#define IMK_SLUG_EXTERN_ROOT_DIR imklib
#include "imklib/IMK_slug_index_ref.h"

#include IMK_SLUG_PARAMS
#include IMK_SLUG_ASSERT
#include IMK_SLUG_LOG

static int add(Params *params) {
  int a, b;
  ASSERT(ParamsMatch(params, 2, PARAM_INT, PARAM_INT));
  ParamsExtract(params, &a, &b);
  return a + b;
}

int main(void) {
  Params params;
  int sum = add(ParamsPush(&params, 2, PARAM_INT, 2005000, PARAM_INT, 41));
  Log1(LOG_INFO, "Sum = %d", sum);
  return 0;
}
