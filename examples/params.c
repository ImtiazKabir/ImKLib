#define USING_IMKLIB_CORE_IMK_PARAMS_H_
#define USING_IMKLIB_IO_IMK_ASSERT
#define USING_IMKLIB_LOGGING_IMK_LOG

#include "imklib/core/IMK_Params.h"
#include "imklib/io/IMK_assert.h"
#include "imklib/logging/IMK_log.h"

int add(Params *params) {
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

