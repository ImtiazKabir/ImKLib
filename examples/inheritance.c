#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_CORE_IMK_MEM
#define USING_IMKLIB_CORE_IMK_STEAP
#define USING_IMKLIB_CORE_IMK_SCOPE
#define USING_IMKLIB_OPTRES_IMK_RESULT
#define USING_IMKLIB_CORE_IMK_PARAMS
#define USING_IMKLIB_LOGGING_IMK_LOG

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_slug_index_ref.h"

#include SLUG_IMK_HEADER_PTR
#include SLUG_IMK_HEADER_MEM
#include SLUG_IMK_HEADER_STEAP
#include SLUG_IMK_HEADER_SCOPE
#include SLUG_IMK_HEADER_PARAMS
#include SLUG_IMK_HEADER_LOG
#include SLUG_IMK_HEADER_RESULT

typedef struct {
  int id;
  void (*greet)(Ptr self);
} Parent;

static void Parent_Greet(Ptr self) {
  Log1(LOG_INFO, "Hello from parent (id = %d)", PTR_DEREF(self, Parent).id);
}

static ResVoid Parent_Constructor(Ptr self, Params *args) {
  int id;
  ParamsExtract(args, &id);
  PTR_DEREF(self, Parent).id = id;
  PTR_DEREF(self, Parent).greet = Parent_Greet;
  return ResVoid_Ok(0);
}

KLASS(ParentKlass) {
  ParentKlass_.size = sizeof(Parent);
  ParentKlass_.ctor = Parent_Constructor;
}

typedef struct {
  Parent parent;
  int id;
  void (*greet)(Ptr self);
} Child;

static void Child_Greet(Ptr self) {
  Log1(LOG_INFO, "Hello from child(id = %d)", PTR_DEREF(self, Child).id);
}

static ResVoid Child_Constructor(Ptr self, Params *args) {
  int id;
  ParamsExtract(args, &id);
  PTR_DEREF(self, Child).id = id;
  PTR_DEREF(self, Child).greet = Child_Greet;
  PTR_DEREF(self, Parent).greet = PTR_DEREF(self, Child).greet;
  return ResVoid_Ok(0);
}

static ResVoid Child_SuperParams(Params *super_args, Params *self_args) {
  int id;
  ParamsExtract(self_args, &id);
  ParamsPush(super_args, 1u, PARAM_INT, 2 * id);
  return ResVoid_Ok(0);
}

KLASS(ChildKlass) {
  ChildKlass_.size = sizeof(Child);
  ChildKlass_.ctor = Child_Constructor;
  ChildKlass_.super_klass = ParentKlass;
  ChildKlass_.super_params = Child_SuperParams;
}

int main(void) {
  SCOPE_INIT(scope, 8);
  Ptr ptr;
  SCOPE_ADD(scope, ptr);

  ptr = KlassAllocP(ChildKlass, NULL, FORCE_HEAP, U32(1), PARAM_INT, 20);

  if (IsOf(ptr, ParentKlass)) {
    Log(LOG_INFO, "It is also a parent");
  }

  Log(LOG_INFO, "From a parent pointer");
  PTR_DEREF(ptr, Parent).greet(ptr);
  Log(LOG_INFO, "From a child pointer");
  PTR_DEREF(ptr, Child).greet(ptr);

  SCOPE_RET(scope, int, 0);
}
