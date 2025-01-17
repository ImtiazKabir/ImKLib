#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_CORE_IMK_MEM
#define USING_IMKLIB_CORE_IMK_STEAP
#define USING_IMKLIB_CORE_IMK_SCOPE
#define USING_IMKLIB_OPTRES_IMK_RESULT
#define USING_IMKLIB_IO_IMK_ASSERT
#define USING_IMKLIB_CORE_IMK_PARAMS
#define USING_IMKLIB_LOGGING_IMK_LOG

#define IMK_SLUG_EXTERN_ROOT_DIR imklib
#include "imklib/IMK_slug_index_ref.h"

#include IMK_SLUG_PTR
#include IMK_SLUG_MEM
#include IMK_SLUG_STEAP
#include IMK_SLUG_SCOPE
#include IMK_SLUG_PARAMS
#include IMK_SLUG_LOG
#include IMK_SLUG_ASSERT
#include IMK_SLUG_RESULT

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

  student = KlassAllocP(StudentKlass, &stack, PREFER_STACK, U32(1), PARAM_INT,
                        2005041);
  Log1(LOG_INFO, "Student ID: %d", ((Student *)student.raw)->id);

  SCOPE_RET(scope, int, 0);
}
