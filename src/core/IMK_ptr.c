#include <string.h>

#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_IO_IMK_ASSERT

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_slug_index_ref.h"

#include SLUG_IMK_HEADER_PTR
#include SLUG_IMK_HEADER_ASSERT

Ptr PtrOwnRaw(void *raw, u32 type) {
  Ptr ptr = {0};

  ASSERT_MSG(raw != NULL, "Can not own a null pointer");
  ptr.raw = raw;

  ptr.flags = PTR_OWNED;
  ASSERT_MSG(type == PTR_STACK || type == PTR_HEAP || type == PTR_STATIC,
             "Unknown type");
  ptr.flags |= type;

  if (type == PTR_STATIC) {
    PtrSetRdOnly(&ptr);
  }

  return ptr;
}

Ptr PtrBorrowRaw(void *raw, u32 type) {
  Ptr ptr = {0};

  ptr.raw = raw;

  ptr.flags = PTR_BORROWED;
  ASSERT_MSG(type == PTR_STACK || type == PTR_HEAP || type == PTR_STATIC,
             "Unknown type");
  ptr.flags |= type;

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

Ptr PtrOff(Ptr ptr, ptrdiff_t amt) {
  Ptr ret = PtrBorrow(ptr);
  ptr.offset += amt;
  ASSERT_MSG((size_t)ptr.offset < ptr.size,
             "Off failed: Trying to move to unallocated area");
  return ret;
}

Ptr PtrBorrow(Ptr ptr) {
  Ptr ret = ptr;
  ASSERT_MSG((ptr.flags & BIN2(1, 1)) != PTR_UNINITIALIZED,
             "Uninitialized smart pointer");
  ASSERT_MSG((ptr.flags & BIN2(1, 1)) != PTR_MOVED,
             "Borrow failed: Context already moved ownership");
  ret.flags &= ~BIN2(1, 1);
  ret.flags |= PTR_BORROWED;
  return ret;
}

Ptr PtrMove(Ptr *ptr) {
  Ptr ret;

  ASSERT_MSG(ptr != NULL, "Opearting on non existent smart pointer");
  ASSERT_MSG((ptr->flags & BIN2(1, 1)) != PTR_UNINITIALIZED,
             "Uninitialized smart pointer");
  ASSERT_MSG((ptr->flags & BIN2(1, 1)) == PTR_OWNED,
             "Move failed: Context does not own pointer");

  ret = *ptr;
  ret.flags &= ~BIN2(1, 1);
  ret.flags |= PTR_OWNED;

  ptr->flags &= ~BIN2(1, 1);
  ptr->flags |= PTR_MOVED;

  return ret;
}
