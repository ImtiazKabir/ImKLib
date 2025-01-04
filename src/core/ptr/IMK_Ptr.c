#define USING_IMKLIB_CORE_PTR_IMK_PTR
#include "imklib/core/ptr/IMK_Ptr.h"

#define USING_IMKLIB_IO_IMK_ASSERT
#include "imklib/io/IMK_assert.h"

#define USING_IMKLIB_LOGGING_IMK_LOG
#include "imklib/logging/IMK_log.h"

#include <string.h>

Ptr PtrOwnRaw(void *raw, boolean stack) {
  Ptr ptr = {0};

  ASSERT_MSG(raw != NULL, "Can not own a null pointer");
  ptr.raw = raw;

  ptr.flags = PTR_OWNED;
  if (stack) {
    ptr.flags |= PTR_STACK;
  }

  return ptr;
}

Ptr PtrBorrowRaw(void *raw, boolean stack) {
  Ptr ptr = {0};

  ptr.raw = raw;

  ptr.flags = PTR_BORROWED;
  if (stack) {
    ptr.flags |= PTR_STACK;
  }

  return ptr;
}

Ptr *PtrSetRdOnly(Ptr *ptr) {
  ASSERT_MSG(ptr != NULL, "Opearting on non existent smart pointer");
  ASSERT_MSG((ptr->flags & BIN2(1, 1)) != PTR_UNINITIALIZED,
             "Uninitialized smart pointer");

  ptr->flags |= PTR_RDONLY;
  return ptr;
}

Ptr *PtrSetSize(Ptr *ptr, size_t size) {
  ASSERT_MSG(ptr != NULL, "Opearting on non existent smart pointer");
  ASSERT_MSG((ptr->flags & BIN2(1, 1)) != PTR_UNINITIALIZED,
             "Uninitialized smart pointer");
  ASSERT_MSG(ptr->size == 0 || ptr->size == size,
             "SetSize failed: can not resize pointer");

  ptr->size = size;
  return ptr;
}

Ptr PtrMove(Ptr ptr, ptrdiff_t amt) {
  Ptr ret = PtrBorrow(ptr);
  ptr.offset += amt;
  ASSERT_MSG((size_t)ptr.offset < ptr.size,
             "Move failed: Trying to move to unallocated area");
  return ret;
}

Ptr PtrBorrow(Ptr ptr) {
  Ptr ret = ptr;
  ASSERT_MSG((ptr.flags & BIN2(1, 1)) != PTR_UNINITIALIZED,
             "Uninitialized smart pointer");
  ASSERT_MSG((ptr.flags & BIN2(1, 1)) != PTR_TRANSFERRED,
             "Borrow failed: Context already transferred ownership");
  ret.flags &= ~BIN2(1, 1);
  ret.flags |= PTR_BORROWED;
  return ret;
}

Ptr PtrTransfer(Ptr *ptr) {
  Ptr ret;

  ASSERT_MSG(ptr != NULL, "Opearting on non existent smart pointer");
  ASSERT_MSG((ptr->flags & BIN2(1, 1)) != PTR_UNINITIALIZED,
             "Uninitialized smart pointer");
  ASSERT_MSG((ptr->flags & BIN2(1, 1)) == PTR_OWNED,
             "Transfer failed: Context does not own pointer");
  ASSERT_MSG((ptr->flags & PTR_STACK) == 0,
             "Transfer failed: Can not transfer a stack pointer");
  ASSERT_MSG((ptr->flags & PTR_STEAP) == 0,
             "Transfer failed: Transferring Steap allocated variable can cause "
             "hard to find bugs");

  ret = *ptr;
  ret.flags &= ~BIN2(1, 1);
  ret.flags |= PTR_OWNED;

  ptr->flags &= ~BIN2(1, 1);
  ptr->flags |= PTR_TRANSFERRED;

  return ret;
}

void PtrDrop(Ptr *ptr) {
  if (ptr == NULL) {
    return;
  }
  if ((ptr->flags & BIN2(1, 1)) != PTR_OWNED) {
    return;
  }
  if (ptr->flags & PTR_STACK) {
    return;
  }
  free(ptr->raw);
  memset(ptr, 0, sizeof(*ptr));
}
