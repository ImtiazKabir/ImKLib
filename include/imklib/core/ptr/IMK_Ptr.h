#ifndef IMKLIB_CORE_PTR_IMK_PTR_H_
#define IMKLIB_CORE_PTR_IMK_PTR_H_

#include <stdlib.h>

#include "../../base/IMK_ints.h"
#include "../../base/IMK_macros.h"

enum {
  IMK_PTR_UNINITIALIZED = BIN2(0, 0),
  IMK_PTR_BORROWED = BIN2(0, 1),
  IMK_PTR_OWNED = BIN2(1, 0),
  IMK_PTR_TRANSFERRED = BIN2(1, 1)
};

#define IMK_PTR_IMK_MEM BIN4(0, 1, 0, 0)

typedef struct {
  void *cptr;
  u8 flags;
} IMK_Ptr;

#define IMK_PTR_NULL {NULL, IMK_PTR_BORROWED}

/*
 * flags
 * +----+----+----+----+----+----+----+----+
 * |    |    |    |    |    | B  | A1 | A0 |
 * +----+----+----+----+----+----+----+----+
 *
 * A1 A0 => Uninitialized / Borrowed / Owned / Transferred / Reserved
 * B => 0 = not imk mem, 1 = imk mem
 *
 */

#endif /* !IMKLIB_CORE_PTR_IMK_PTR_H_ */

