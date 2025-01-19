#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#define USING_NAMESPACE_IMK_CORE
#include SLUG_IMK_HEADER_CORE

typedef struct {
  int (*get_magnitude)(Ptr implementation);
} Vector;

KLASS(VectorInterface) {
  VectorInterface_.size = sizeof(Vector);
}

static int Vector_GetMagnitude(Ptr implementation_b) {
  SCOPE_INIT(scope, 8);
  STACK_INIT(stack, 128);
  Ptr self;
  Ptr implementation = PtrBorrow(implementation_b);
  SCOPE_ADD(scope, implementation);
  SCOPE_ADD(scope, self);

  self = GetImplOfP(GetKlass(implementation), VectorInterface, &stack, PREFER_STACK);

  SCOPE_RET(scope, int , PTR_DEREF(self, Vector).get_magnitude(implementation));
}

typedef struct {
  int x;
  int y;
} Vector2;

static int Vector2_GetMagnitude(Ptr self_b) {
  int x = PTR_DEREF(self_b, Vector2).x;
  int y = PTR_DEREF(self_b, Vector2).y;
  return x * x + y * y;
}

static void Vector2_ImplementationFiller(Ptr interface) {
  ASSERT(IsOf(interface, VectorInterface));
  PTR_DEREF(interface, Vector).get_magnitude = Vector2_GetMagnitude;
}

KLASS(Vector2Klass) {
  Vector2Klass_.size = sizeof(Vector2);
  Vector2Klass_.impl_filler = Vector2_ImplementationFiller;
}

typedef struct {
  int x;
  int y;
  int z;
} Vector3;

static int Vector3_GetMagnitude(Ptr self_b) {
  int x = PTR_DEREF(self_b, Vector3).x;
  int y = PTR_DEREF(self_b, Vector3).y;
  int z = PTR_DEREF(self_b, Vector3).z;
  return x * x + y * y + z * z;
}

static void Vector3_ImplementationFiller(Ptr interface) {
  ASSERT(IsOf(interface, VectorInterface));
  PTR_DEREF(interface, Vector).get_magnitude = Vector3_GetMagnitude;
}

KLASS(Vector3Klass) {
  Vector3Klass_.size = sizeof(Vector3);
  Vector3Klass_.impl_filler = Vector3_ImplementationFiller;
}

int main(void) {
  SCOPE_INIT(scope, 8);
  STACK_INIT(stack, 128);
  Ptr vec2;
  Ptr vec3;
  SCOPE_ADD(scope, vec2);
  SCOPE_ADD(scope, vec3);

  vec2 = KlassAllocP(Vector2Klass, &stack, PREFER_STACK, U32(0));
  PTR_DEREF(vec2, Vector2).x = 3;
  PTR_DEREF(vec2, Vector2).y = 4;

  vec3 = KlassAllocP(Vector3Klass, &stack, PREFER_STACK, U32(0));
  PTR_DEREF(vec3, Vector3).x = 3;
  PTR_DEREF(vec3, Vector3).y = 4;
  PTR_DEREF(vec3, Vector3).z = 12;

  Log2(LOG_INFO, "%d %d", Vector_GetMagnitude(vec2), Vector_GetMagnitude(vec3));

  SCOPE_RET(scope, int, 0);
}


