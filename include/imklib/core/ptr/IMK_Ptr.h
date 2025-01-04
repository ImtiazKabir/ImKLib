#ifndef IMKLIB_CORE_PTR_IMK_PTR_H_
#define IMKLIB_CORE_PTR_IMK_PTR_H_

#include <stddef.h>
#include <stdlib.h>

#include "../../base/IMK_macros.h"
#include "../../base/IMK_types.h"

typedef struct {
  void *raw;
  u8 flags;
  size_t size;
  ptrdiff_t offset;
} IMK_Ptr;

/*
 * flags
 * +----+----+----+----+----+----+----+----+
 * |    |    | E  | D  | C  | B  | A1 | A0 |
 * +----+----+----+----+----+----+----+----+
 *
 * A1 A0 => Uninitialized / Borrowed / Owned / Transferred
 * B => Stack or Heap
 * C => Steap?
 * D => ImKMem?
 * E => read only?
 */

enum {
  IMK_PTR_UNINITIALIZED = BIN2(0, 0),
  IMK_PTR_BORROWED = BIN2(0, 1),
  IMK_PTR_OWNED = BIN2(1, 0),
  IMK_PTR_TRANSFERRED = BIN2(1, 1)
};

enum {
  IMK_PTR_STACK = 1 << 2,
  IMK_PTR_STEAP = 1 << 3,
  IMK_PTR_IMKMEM = 1 << 4,
  IMK_PTR_RDONLY = 1 << 5
};

IMK_Ptr IMK_PtrOwnRaw(void *raw, boolean stack);
IMK_Ptr IMK_PtrBorrowRaw(void *raw, boolean stack);
IMK_Ptr *IMK_PtrSetRdOnly(IMK_Ptr *ptr);
IMK_Ptr *IMK_PtrSetSize(IMK_Ptr *ptr, size_t size);
IMK_Ptr IMK_PtrMove(IMK_Ptr ptr, ptrdiff_t amt);
IMK_Ptr IMK_PtrBorrow(IMK_Ptr ptr);
IMK_Ptr IMK_PtrTransfer(IMK_Ptr *ptr);
void IMK_PtrDrop(IMK_Ptr *ptr);

#ifdef USING_IMKLIB_CORE_PTR_IMK_PTR
typedef IMK_Ptr Ptr;

#define PTR_UNINITIALIZED IMK_PTR_UNINITIALIZED
#define PTR_BORROWED IMK_PTR_BORROWED
#define PTR_OWNED IMK_PTR_OWNED
#define PTR_TRANSFERRED IMK_PTR_TRANSFERRED
#define PTR_STACK IMK_PTR_STACK
#define PTR_STEAP IMK_PTR_STEAP
#define PTR_IMKMEM IMK_PTR_IMKMEM
#define PTR_RDONLY IMK_PTR_RDONLY

#define PtrOwnRaw IMK_PtrOwnRaw
#define PtrBorrowRaw IMK_PtrBorrowRaw
#define PtrSetRdOnly IMK_PtrSetRdOnly
#define PtrSetSize IMK_PtrSetSize
#define PtrMove IMK_PtrMove
#define PtrBorrow IMK_PtrBorrow
#define PtrTransfer IMK_PtrTransfer
#define PtrDrop IMK_PtrDrop

#endif /* USING_IMKLIB_CORE_PTR_IMK_PTR */

#endif /* !IMKLIB_CORE_PTR_IMK_PTR_H_ */
