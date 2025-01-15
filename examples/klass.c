#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_CORE_IMK_MEM
#define USING_IMKLIB_CORE_IMK_STEAP
#define USING_IMKLIB_CORE_IMK_SCOPE
#define USING_IMKLIB_OPTRES_IMK_OPTION
#define USING_IMKLIB_OPTRES_IMK_RESULT
#define USING_IMKLIB_IO_IMK_ASSERT
#define USING_IMKLIB_CORE_IMK_PARAMS
#define USING_IMKLIB_LOGGING_IMK_LOG

#include "imklib/core/IMK_ptr.h"
#include "imklib/core/IMK_mem.h"
#include "imklib/core/IMK_steap.h"
#include "imklib/core/IMK_scope.h"
#include "imklib/core/IMK_params.h"
#include "imklib/optres/IMK_option.h"
#include "imklib/optres/IMK_result.h"
#include "imklib/io/IMK_assert.h"
#include "imklib/logging/IMK_log.h"


typedef struct {
  int id;
} Student;

ResVoid Constructor(Ptr self_, Params *args) {
  Student self = PTR_DEREF(self_, Student);
  int id;
  Log(LOG_TRACE, "Inside constructor");
  ASSERT(ParamsMatch(args, 1, PARAM_INT));
  ParamsExtract(args, &id);
  self.id = id;
  return ResVoid_Ok(0);
}

KLASS(StudentKlass) {
  StudentKlass_.size = sizeof(Student);
  StudentKlass_.ctor = Constructor;
}

int main(void) {
  SCOPE_INIT(scope, 8);
  STACK_INIT(stack, 100);
  Ptr student;
  SCOPE_ADD(scope, student);

  student = KlassAllocP(StudentKlass, &stack, PREFER_STACK, U32(1), PARAM_INT, 2005041);
  Log1(LOG_INFO, "Student ID: %d", ((Student *)student.raw)->id);

  SCOPE_RET(scope, int, 0);
}



