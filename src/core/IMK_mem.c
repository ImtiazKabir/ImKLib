#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_CORE_IMK_MEM
#define USING_IMKLIB_CORE_IMK_STEAP
#define USING_IMKLIB_OPTRES_IMK_OPTION
#define USING_IMKLIB_IO_IMK_ASSERT

#include "imklib/core/IMK_ptr.h"
#include "imklib/core/IMK_mem.h"
#include "imklib/core/IMK_steap.h"
#include "imklib/optres/IMK_option.h"

#include <string.h>

Ptr ToStr(Ptr ptr) {
  Ptr p = PtrOwnRaw((void *)"PtrToStr called", PTR_STATIC);
  (void)ptr;
  return PtrMove(&p);
}

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

Ptr VanillaAllocP(void *stack, size_t n, IMK_SteapMode mode) {
  return OptPtr_Unwrap(VanillaAlloc(stack, n, mode));
}

Ptr TypedAllocP(char const *type_hint, void *stack, size_t n, IMK_SteapMode mode) {
  return OptPtr_Unwrap(TypedAlloc(type_hint, stack, n, mode));
}

void Drop(Ptr *ptr) {
  if (ptr == NULL) {
    return;
  }
  if ((ptr->flags & BIN2(1, 1)) != PTR_OWNED) {
    return;
  }
  if ((ptr->flags & BIN2(1, 1) << 2) == PTR_HEAP) {
    if (ptr->flags & PTR_IMK_MEM) {
      free((BlockHeader *)ptr->raw - 1);
    } else {
      free(ptr->raw);
    }
  }
  memset(ptr, 0, sizeof(*ptr));
}

