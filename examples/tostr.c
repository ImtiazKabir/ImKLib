#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#define USING_NAMESPACE_IMK_CORE
#include SLUG_IMK_HEADER_CORE

typedef struct {
  int id;
} Student;

static ResVoid Student_Constructor(Ptr self, Params *args) {
  int id;
  ASSERT(ParamsMatch(args, 1, PARAM_INT));
  ParamsExtract(args, &id);
  PTR_DEREF(self, Student).id = id;
  return ResVoid_Ok(0);
}

static OptPtr Student_ToStr(Ptr self, void *stack, SteapMode mode) {
  size_t n = (size_t) csnprintf(NULL, 0, "Student(%d)", PTR_DEREF(self, Student).id);
  OptPtr opt = TypedAlloc("String", stack, n + 1, mode);
  Ptr ptr;
  OPTION_TRY(ptr, OptPtr, opt, OptPtr);
  csnprintf(ptr.raw, n + 1, "Student(%d)", PTR_DEREF(self, Student).id);
  return OptPtr_Some(PtrMove(&ptr));
}

KLASS(StudentKlass) {
  StudentKlass_.size = sizeof(Student);
  StudentKlass_.ctor = Student_Constructor;
  StudentKlass_.to_str = Student_ToStr;
}

int main(void) {
  SCOPE_INIT(scope, 8);
  STACK_INIT(stack, 100);
  Ptr student;
  SCOPE_ADD(scope, student);

  student = KlassAllocP(StudentKlass, &stack, PREFER_STACK, U32(1), PARAM_INT,
                        2005041);
  /*Log1(LOG_INFO, "Hello: %obj", student);*/
  PrintF("Hello: %obj\n", student);

  SCOPE_RET(scope, int, 0);
}
