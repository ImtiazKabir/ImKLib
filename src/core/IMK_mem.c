#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_CORE_IMK_MEM
#define USING_IMKLIB_CORE_IMK_STEAP
#define USING_IMKLIB_OPTRES_IMK_OPTION
#define USING_IMKLIB_OPTRES_IMK_RESULT
#define USING_IMKLIB_IO_IMK_ASSERT
#define USING_IMKLIB_CORE_IMK_PARAMS

#include "imklib/core/IMK_ptr.h"
#include "imklib/core/IMK_mem.h"
#include "imklib/core/IMK_steap.h"
#include "imklib/core/IMK_params.h"
#include "imklib/optres/IMK_option.h"
#include "imklib/optres/IMK_result.h"
#include "imklib/io/IMK_assert.h"

#include <string.h>
#include <stdarg.h>

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

static void *HeapAllocRaw(size_t n) {
  return calloc(n, 1);
}

static void *AllocRaw(void *stack, size_t n, SteapMode mode) {
  void *ret = NULL;
  switch(mode) {
  case PREFER_STACK:
    if ((ret = StackAllocRaw(stack, n))) return ret;
    if ((ret = HeapAllocRaw(n))) return ret;
    break;
  case FORCE_STACK:
    if ((ret = StackAllocRaw(stack, n))) return ret;
    break;
  case PREFER_HEAP:
    if ((ret = HeapAllocRaw(n))) return ret;
    if ((ret = StackAllocRaw(stack, n))) return ret;
    break;
  case FORCE_HEAP:
    if ((ret = HeapAllocRaw(n))) return ret;
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
  } else if (stack->mem <= (char *)rptr && (char *)rptr < stack->mem + stack->cap) {
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

OptPtr TypedAlloc(char const *type_hint, void *stack_, size_t n, IMK_SteapMode mode) {
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
  } else if (stack->mem <= (char *)header && (char *)header < stack->mem + stack->cap) {
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

Ptr TypedAllocP(char const *type_hint, void *stack, size_t n, IMK_SteapMode mode) {
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

static Klass *GetKlass(Ptr ptr) {
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
  if (klass != NULL) {
    return OptPtr_Some(klass->to_str(ptr.raw));
  }
  header = GetHeader(ptr);
  if (header == NULL) {
    Ptr str;
    char cstr[48] = {0};
    sprintf(cstr, "%p", ptr.raw);
    OPTION_TRY(str, OptPtr, TypedAlloc("String", stack, strlen(cstr) + 1, mode), OptPtr);
    strcat(str.raw, cstr);
    return OptPtr_Some(PtrMove(&str));
  }
  if (strcmp(header->type.hint, "String") == 0) {
    Ptr str;
    OPTION_TRY(str, OptPtr, TypedAlloc("String", stack, strlen(ptr.raw) + 1, mode), OptPtr);
    strcat(str.raw, ptr.raw);
    return OptPtr_Some(PtrMove(&str));
  } else {
    Ptr str;
    char cstr[48] = {0};
    sprintf(cstr, "%s@%p", GetTypeHint(ptr), ptr.raw);
    OPTION_TRY(str, OptPtr, TypedAlloc("String", stack, strlen(cstr) + 1, mode), OptPtr);
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
  return klass->hash(ptr.raw);
}


int Compare(Ptr p1, Ptr p2) {
  Klass *k1 = GetKlass(p1);
  Klass *k2 = GetKlass(p2);
  if (k1 == NULL || k2 == NULL || k1 != k2) {
    return (int)((char *)p1.raw - (char *)p2.raw);
  }
  return k1->compare(p1.raw, p2.raw);
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
  } else if (stack->mem <= (char *)header && (char *)header < stack->mem + stack->cap) {
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

static ResVoid CtorRecurse(void *self, Klass *klass, Params *params) {
  Params super_params = {0};

  if (klass->super_klass != NULL) {
    ASSERT(klass->super_params);
    klass->super_params(&super_params, params);
    return CtorRecurse(self, klass->super_klass, &super_params);
  }

  return klass->ctor(self, params);
}

static ResPtr KlassAllocV(Klass *klass, void *stack, SteapMode mode, va_list list) {
  Ptr ret;
  Params params = {0};
  u32 len;

  ret = OptPtr_Unwrap(AllocKlass(klass, stack, mode)); /* TODO do not use unwrap, change it to use errors */
  len = va_arg(list, u32);
  if (len != 0u) {
    ParamsVPush(&params, len, list);
  }

  RESULT_TRY(ResVoid, CtorRecurse(ret.raw, klass, &params), ResPtr);

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

static void CloneRecurse(void *from, Klass *klass, void *to) {
  if (klass == NULL) {
    return;
  }
  CloneRecurse(from, klass->super_klass, to);
  klass->clone(to, from);
}

OptPtr Clone(Ptr ptr, void *stack, SteapMode mode) {
  Ptr cloned;
  Klass *klass = GetKlass(ptr);
  ASSERT(klass);
  ASSERT(klass->clone);
  OPTION_TRY(cloned, OptPtr, AllocKlass(klass, stack, mode), OptPtr);
  CloneRecurse(ptr.raw, klass, cloned.raw);
  return OptPtr_Some(cloned);
}

Ptr CloneP(Ptr ptr, void *stack, SteapMode mode) {
  return OptPtr_Unwrap(Clone(ptr, stack, mode));
}

static void AssignRecurse(void *from, Klass *klass, void *to) {
  if (klass == NULL) {
    return;
  }
  AssignRecurse(from, klass->super_klass, to);
  klass->clone(to, from);
}

void Assign(Ptr to, Ptr from) {
  Klass *to_klass = GetKlass(to);
  Klass *from_klass = GetKlass(from);
  
  ASSERT(to_klass);
  ASSERT(from_klass);
  ASSERT(to_klass == from_klass);
  
  AssignRecurse(from.raw, to_klass, to.raw);
}

static void DtorRecurse(void *self, Klass *klass) {
  if (klass == NULL) {
    return;
  }
  DtorRecurse(self, klass->super_klass);
  if (klass->dtor) {
    klass->dtor(self);
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
  if ((ptr->flags & BIN2(1, 1) << 2) == PTR_HEAP) {
    if (ptr->flags & PTR_IMK_MEM) {
      BlockHeader *header = GetHeader(*ptr);
      ASSERT(header);
      if (header->allockey == KLASS_ALLOC_KEY) {
        Klass *klass = header->type.klass;
        ASSERT(klass);
        DtorRecurse(ptr->raw, klass);
      }
      free(header);
    } else {
      free(ptr->raw);
    }
  }
  memset(ptr, 0, sizeof(*ptr));
}

