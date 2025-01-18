#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_slug_index_ref.h"

#define USING_NAMESPACE_IMK_CORE
#include SLUG_IMK_HEADER_CORE

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
