#ifndef IMK_PTR_H_99JPJ0NI06PW128Q
#define IMK_PTR_H_99JPJ0NI06PW128Q

#include <stddef.h>
#include <stdlib.h>

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_INTS

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_MACROS

typedef struct {
  void *raw;
  u8 flags;
  size_t size;
  ptrdiff_t offset;
} IMK_Ptr;

/*
 * flags
 * +----+----+----+----+----+----+----+----+
 * |    |    | E  | D  | B1 | B0 | A1 | A0 |
 * +----+----+----+----+----+----+----+----+
 *
 * A1 A0 => Uninitialized / Borrowed / Owned / Moved
 * B1 B0 => None / Stack / Heap / Static
 * D => ImKMem?
 * E => read only?
 */

#define IMK_PTR_DEREF(p, T) (*((T *)(p).raw))

enum {
  IMK_PTR_UNINITIALIZED = BIN2(0, 0),
  IMK_PTR_BORROWED = BIN2(0, 1),
  IMK_PTR_OWNED = BIN2(1, 0),
  IMK_PTR_MOVED = BIN2(1, 1)
};

enum {
  IMK_PTR_STACK = BIN2(0, 1) << 2,
  IMK_PTR_HEAP = BIN2(1, 0) << 2,
  IMK_PTR_STATIC = BIN2(1, 1) << 2
};

enum { IMK_PTR_IMK_MEM = 1 << 4, IMK_PTR_RDONLY = 1 << 5 };

IMK_Ptr IMK_PtrOwnRaw(void *raw, u32 type);
IMK_Ptr IMK_PtrBorrowRaw(void *raw, u32 type);
IMK_Ptr *IMK_PtrSetRdOnly(IMK_Ptr *ptr);
IMK_Ptr *IMK_PtrSetSize(IMK_Ptr *ptr, size_t size);
IMK_Ptr IMK_PtrOff(IMK_Ptr ptr, ptrdiff_t amt);
IMK_Ptr IMK_PtrBorrow(IMK_Ptr ptr);
IMK_Ptr IMK_PtrMove(IMK_Ptr *ptr);

void IMK_Drop(IMK_Ptr *ptr);

#ifdef USING_NAMESPACE_IMK_PTR
#include "IMK_index_ref.slug"
#include SLUG_IMK_ATTACH_PTR
#endif /* USING_NAMESPACE_IMK_PTR */

#endif /* !IMK_PTR_H_99JPJ0NI06PW128Q */
