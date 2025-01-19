#define USING_NAMESPACE_IMK_PTR
#define USING_NAMESPACE_IMK_MEM
#define USING_NAMESPACE_IMK_STEAP
#define USING_NAMESPACE_IMK_OPTION
#define USING_NAMESPACE_IMK_RESULT
#define USING_NAMESPACE_IMK_ASSERT
#define USING_NAMESPACE_IMK_PARAMS

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#include SLUG_IMK_HEADER_PTR
#include SLUG_IMK_HEADER_MEM
#include SLUG_IMK_HEADER_STEAP
#include SLUG_IMK_HEADER_PARAMS
#include SLUG_IMK_HEADER_OPTION
#include SLUG_IMK_HEADER_RESULT
#include SLUG_IMK_HEADER_ASSERT

#include <stdarg.h>
#include <string.h>

static void *StackAllocRaw(void *stack_, size_t n) {
  STACK(1) *stack = stack_;
  if (stack == NULL) {
    return NULL;
  }
  if ((size_t)stack->off + n >= stack->cap) {
    return NULL;
  }
  {
    char *ret = stack->mem + stack->off;
    stack->off += n;
    return ret;
  }
}

static void *HeapAllocRaw(size_t n) { return calloc(n, 1); }

static void *AllocRaw(void *stack, size_t n, SteapMode mode) {
  void *ret = NULL;
  switch (mode) {
  case PREFER_STACK:
    if ((ret = StackAllocRaw(stack, n)))
      return ret;
    if ((ret = HeapAllocRaw(n)))
      return ret;
    break;
  case FORCE_STACK:
    if ((ret = StackAllocRaw(stack, n)))
      return ret;
    break;
  case PREFER_HEAP:
    if ((ret = HeapAllocRaw(n)))
      return ret;
    if ((ret = StackAllocRaw(stack, n)))
      return ret;
    break;
  case FORCE_HEAP:
    if ((ret = HeapAllocRaw(n)))
      return ret;
    break;
  }
  return NULL;
}

OptPtr VanillaAlloc(void *stack_, size_t n, SteapMode mode) {
  Ptr ptr = {0};
  STACK(1) *stack = stack_;
  void *rptr = AllocRaw(stack, n, mode);
  u32 where;

  if (rptr == NULL) {
    return OptPtr_None();
  }

  if (stack == NULL) {
    where = PTR_HEAP;
  } else if (stack->mem <= (char *)rptr &&
             (char *)rptr < stack->mem + stack->cap) {
    where = PTR_STACK;
  } else {
    where = PTR_HEAP;
  }

  ptr = PtrOwnRaw(rptr, where);
  PtrSetSize(&ptr, n);
  return OptPtr_Some(ptr);
}

Ptr VanillaAllocP(void *stack, size_t n, IMK_SteapMode mode) {
  return OptPtr_Unwrap(VanillaAlloc(stack, n, mode));
}

OptPtr TypedAlloc(char const *type_hint, void *stack_, size_t n,
                  IMK_SteapMode mode) {
  Ptr ptr = {0};
  STACK(1) *stack = stack_;
  BlockHeader *header;
  u32 where;

  header = AllocRaw(stack, n + sizeof(BlockHeader), mode);

  if (header == NULL) {
    return OptPtr_None();
  }

  if (stack == NULL) {
    where = PTR_HEAP;
  } else if (stack->mem <= (char *)header &&
             (char *)header < stack->mem + stack->cap) {
    where = PTR_STACK;
  } else {
    where = PTR_HEAP;
  }

  header->size = n;
  header->allockey = DATA_ALLOC_KEY;
  header->type.hint = type_hint;

  ptr = PtrOwnRaw(header + 1, where);
  PtrSetSize(&ptr, n);
  ptr.flags |= PTR_IMK_MEM;
  return OptPtr_Some(ptr);
}

Ptr TypedAllocP(char const *type_hint, void *stack, size_t n,
                IMK_SteapMode mode) {
  return OptPtr_Unwrap(TypedAlloc(type_hint, stack, n, mode));
}

static BlockHeader *GetHeader(Ptr ptr) {
  BlockHeader *header;
  if ((ptr.flags & PTR_IMK_MEM) == 0) {
    return NULL;
  }
  header = (BlockHeader *)ptr.raw - 1;
  return header;
}

char const *GetTypeHint(Ptr ptr) {
  BlockHeader *header = GetHeader(ptr);
  if (header == NULL) {
    return NULL;
  }
  if (header->allockey == DATA_ALLOC_KEY) {
    return header->type.hint;
  } else {
    return header->type.klass->type;
  }
}

Klass *GetKlass(Ptr ptr) {
  BlockHeader *header = GetHeader(ptr);
  if (header == NULL) {
    return NULL;
  }
  if (header->allockey == DATA_ALLOC_KEY) {
    return NULL;
  }
  return header->type.klass;
}

int IsOf(Ptr ptr, Klass *klass) {
  Klass *this_klass = GetKlass(ptr);
  while (this_klass) {
    if (this_klass == klass) {
      return TRUE;
    }
    this_klass = this_klass->super_klass;
  }
  return FALSE;
}

OptPtr ToStr(Ptr ptr, void *stack, SteapMode mode) {
  Klass *klass = GetKlass(ptr);
  BlockHeader *header;
  if (klass != NULL && klass->to_str != NULL) {
    return klass->to_str(PtrBorrow(ptr), stack, mode);
  }
  header = GetHeader(ptr);
  if (header == NULL) {
    Ptr str;
    char cstr[48] = {0};
    sprintf(cstr, "%p", ptr.raw);
    OPTION_TRY(str, OptPtr, TypedAlloc("String", stack, strlen(cstr) + 1, mode),
               OptPtr);
    strcat(str.raw, cstr);
    return OptPtr_Some(PtrMove(&str));
  }
  if (strcmp(header->type.hint, "String") == 0) {
    Ptr str;
    OPTION_TRY(str, OptPtr,
               TypedAlloc("String", stack, strlen(ptr.raw) + 1, mode), OptPtr);
    strcat(str.raw, ptr.raw);
    return OptPtr_Some(PtrMove(&str));
  } else {
    Ptr str;
    char cstr[48] = {0};
    sprintf(cstr, "%s@%p", GetTypeHint(ptr), ptr.raw);
    OPTION_TRY(str, OptPtr, TypedAlloc("String", stack, strlen(cstr) + 1, mode),
               OptPtr);
    strcat(str.raw, cstr);
    return OptPtr_Some(PtrMove(&str));
  }
}

Ptr ToStrP(Ptr ptr, void *stack, SteapMode mode) {
  return OptPtr_Unwrap(ToStr(ptr, stack, mode));
}

size_t Hash(Ptr ptr) {
  Klass *klass = GetKlass(ptr);
  if (klass == NULL) {
    return 0;
  }
  return klass->hash(PtrBorrow(ptr));
}

int Compare(Ptr p1, Ptr p2) {
  Klass *k1 = GetKlass(p1);
  Klass *k2 = GetKlass(p2);
  if (k1 == NULL || k2 == NULL || k1 != k2) {
    return (int)((char *)p1.raw - (char *)p2.raw);
  }
  return k1->compare(PtrBorrow(p1), PtrBorrow(p2));
}

static void InitAncestryLineRecurse(Klass *klass) {
  if (klass == NULL) {
    return;
  }
  ASSERT(klass->klass_init);
  klass->klass_init();
  klass->klass_init = NULL;
  InitAncestryLineRecurse(klass->super_klass);
}

static OptPtr AllocKlass(Klass *klass, void *stack_, SteapMode mode) {
  STACK(1) *stack = stack_;
  BlockHeader *header;
  u32 where;
  Ptr ptr;

  ASSERT(klass);
  if (klass->klass_init != NULL) {
    InitAncestryLineRecurse(klass);
  }
  header = AllocRaw(stack, klass->size + sizeof(BlockHeader), mode);
  if (header == NULL) {
    return OptPtr_None();
  }

  if (stack == NULL) {
    where = PTR_HEAP;
  } else if (stack->mem <= (char *)header &&
             (char *)header < stack->mem + stack->cap) {
    where = PTR_STACK;
  } else {
    where = PTR_HEAP;
  }

  header->size = klass->size;
  header->allockey = KLASS_ALLOC_KEY;
  header->type.klass = klass;

  ptr = PtrOwnRaw(header + 1, where);
  PtrSetSize(&ptr, header->size);
  ptr.flags |= PTR_IMK_MEM;
  return OptPtr_Some(ptr);
}

static ResVoid CtorRecurse(Ptr self, Klass *klass, Params *params) {
  if (klass->super_klass) {
    Params super_params = {0};
    if (klass->super_params) {
      klass->super_params(&super_params, params);
    } else {
      ParamsCopy(&super_params, params);
    }
    RESULT_TRY(ResVoid, CtorRecurse(self, klass->super_klass, &super_params),
               ResVoid);
  }

  if (klass->ctor) {
    return klass->ctor(PtrBorrow(self), params);
  }
  return ResVoid_Ok(0);
}

static ResPtr KlassAllocV(Klass *klass, void *stack, SteapMode mode,
                          va_list list) {
  Ptr ret;
  Params params = {0};
  u32 len;

  ret = OptPtr_Unwrap(
      AllocKlass(klass, stack,
                 mode)); /* TODO do not use unwrap, change it to use errors */
  len = va_arg(list, u32);
  if (len != 0u) {
    ParamsVPush(&params, len, list);
  }

  RESULT_TRY(ResVoid, CtorRecurse(ret, klass, &params), ResPtr);

  return ResPtr_Ok(ret);
}

ResPtr IMK_KlassAlloc(Klass *klass, void *stack, SteapMode mode, ...) {
  ResPtr res;
  va_list list;
  va_start(list, mode);
  res = KlassAllocV(klass, stack, mode, list);
  va_end(list);
  return res;
}

Ptr KlassAllocP(Klass *klass, void *stack, SteapMode mode, ...) {
  Ptr ptr;
  va_list list;
  va_start(list, mode);
  ptr = ResPtr_Unwrap(KlassAllocV(klass, stack, mode, list));
  va_end(list);
  return ptr;
}

static void CloneRecurse(Ptr from, Klass *klass, Ptr to) {
  if (klass == NULL) {
    return;
  }
  CloneRecurse(from, klass->super_klass, to);
  klass->clone(PtrBorrow(to), PtrBorrow(from));
}

OptPtr Clone(Ptr ptr, void *stack, SteapMode mode) {
  Ptr cloned;
  Klass *klass = GetKlass(ptr);
  ASSERT(klass);
  ASSERT(klass->clone);
  OPTION_TRY(cloned, OptPtr, AllocKlass(klass, stack, mode), OptPtr);
  CloneRecurse(ptr, klass, cloned);
  return OptPtr_Some(cloned);
}

Ptr CloneP(Ptr ptr, void *stack, SteapMode mode) {
  return OptPtr_Unwrap(Clone(ptr, stack, mode));
}

static void AssignRecurse(Ptr from, Klass *klass, Ptr to) {
  if (klass == NULL) {
    return;
  }
  AssignRecurse(from, klass->super_klass, to);
  klass->clone(PtrBorrow(to), PtrBorrow(from));
}

void Assign(Ptr to, Ptr from) {
  Klass *to_klass = GetKlass(to);
  Klass *from_klass = GetKlass(from);

  ASSERT(to_klass);
  ASSERT(from_klass);
  ASSERT(to_klass == from_klass);

  AssignRecurse(from, to_klass, to);
}

static void DtorRecurse(Ptr self, Klass *klass) {
  if (klass == NULL) {
    return;
  }
  DtorRecurse(self, klass->super_klass);
  if (klass->dtor) {
    klass->dtor(PtrBorrow(self));
  }
}

void Drop(Ptr *ptr) {
  if (ptr == NULL) {
    return;
  }
  if (ptr->raw == NULL) {
    return;
  }
  if ((ptr->flags & BIN2(1, 1)) != PTR_OWNED) {
    return;
  }

  if (ptr->flags & PTR_IMK_MEM) {
    BlockHeader *header = GetHeader(*ptr);
    ASSERT(header);
    if (header->allockey == KLASS_ALLOC_KEY) {
      Klass *klass = header->type.klass;
      ASSERT(klass);
      DtorRecurse(*ptr, klass);
    }
  }

  if ((ptr->flags & BIN2(1, 1) << 2) == PTR_HEAP) {
    if (ptr->flags & PTR_IMK_MEM) {
      BlockHeader *header = GetHeader(*ptr);
      ASSERT(header);
      free(header);
    } else {
      free(ptr->raw);
    }
  }
  memset(ptr, 0, sizeof(*ptr));
}

ResPtr GetImplOf(Klass *implementation, Klass *interface, void *stack, SteapMode mode) {
  Ptr interface_instance;
  RESULT_TRY_OR(interface_instance, ResPtr, KlassAlloc(interface, stack, mode), ResPtr);
  implementation->impl_filler(interface_instance);
  return ResPtr_Ok(interface_instance);
}

Ptr GetImplOfP(Klass *implementation, Klass *interface, void *stack, SteapMode mode) {
  return ResPtr_Unwrap(GetImplOf(implementation, interface, stack, mode));
}


