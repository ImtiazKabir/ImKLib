#ifndef IMKLIB_CORE_PTR_IMK_PTR_H_
#define IMKLIB_CORE_PTR_IMK_PTR_H_

#include <stdlib.h>
#include <stddef.h>

#include "../../base/IMK_ints.h"
#include "../../base/IMK_macros.h"

enum {
  IMK_PTR_UNINITIALIZED = BIN2(0, 0),
  IMK_PTR_BORROWED = BIN2(0, 1),
  IMK_PTR_OWNED = BIN2(1, 0),
  IMK_PTR_TRANSFERRED = BIN2(1, 1)
};

typedef struct {
  void *cptr;
  u8 flags;                 /* description is below struct definition */
  ptrdiff_t back_offset;    /* in bytes */
  ptrdiff_t fwd_offset;     /* in bytes */
} IMK_Ptr;

/*
 * flags
 * +----+----+----+----+----+----+----+----+
 * |    |    | E  | D  | C  | B  | A1 | A0 |
 * +----+----+----+----+----+----+----+----+
 *
 * A1 A0 => Uninitialized / Borrowed / Owned / Transferred / Reserved
 * B => Stack or Heap
 * C => Steap?
 * D => ImKMem?
 * E => read only?
 */

#endif /* !IMKLIB_CORE_PTR_IMK_PTR_H_ */

