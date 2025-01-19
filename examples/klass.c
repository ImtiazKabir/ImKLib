#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#define USING_NAMESPACE_IMK_CORE
#include SLUG_IMK_HEADER_CORE

typedef struct {
  int id;
} Student;

static ResVoid Student_Constructor(Ptr self, Params *args) {
  int id;
  Log(LOG_TRACE, "Inside constructor");
  ASSERT(ParamsMatch(args, 1, PARAM_INT));
  ParamsExtract(args, &id);
  PTR_DEREF(self, Student).id = id;
  return ResVoid_Ok(0);
}


KLASS(StudentKlass) {
  StudentKlass_.size = sizeof(Student);
  StudentKlass_.ctor = Student_Constructor;
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
