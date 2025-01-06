#ifndef IMKLIB_CORE_IMK_SCOPE_H_
#define IMKLIB_CORE_IMK_SCOPE_H_

#include <stdlib.h>

#include "../base/IMK_ints.h"
#include "../base/IMK_macros.h"
#include "../io/IMK_assert.h"
#include "IMK_ptr.h"

#define IMK_SCOPE(c)                                                           \
  struct {                                                                     \
    IMK_Ptr *ptrs[c];                                                          \
    size_t len;                                                                \
  }

#define IMK_SCOPE_INIT(s, c) SCOPE(c) s = {{0}, 0}
#define IMK_SCOPE_ADD(s, p)                                                    \
  IMK_ASSERT_MSG(s.len < ARRAY_COUNT(s.ptrs),                                  \
                 "Scope too small, can not add pointer");                      \
  s.ptrs[s.len++] = &p;

#define IMK_SCOPE_END(s)                                                       \
  {                                                                            \
    FOR(u32 s_iter_2005041_, s_iter_2005041_ = 0; s_iter_2005041_ < s.len;     \
        s_iter_2005041_++, IMK_PtrDrop(s.ptrs[s_iter_2005041_]);)              \
  }
#define IMK_SCOPE_RET(s, T, x)                                                 \
  {                                                                            \
    T s_ret_2005041_ = x;                                                      \
    IMK_SCOPE_END(s);                                                          \
    return s_ret_2005041_;                                                     \
  }

#ifdef USING_IMKLIB_CORE_IMK_SCOPE
#define SCOPE IMK_SCOPE
#define SCOPE_INIT IMK_SCOPE_INIT
#define SCOPE_ADD IMK_SCOPE_ADD
#define SCOPE_END IMK_SCOPE_END
#define SCOPE_RET IMK_SCOPE_RET
#endif /* USING_IMKLIB_CORE_IMK_SCOPE */

#endif /* !IMKLIB_CORE_IMK_SCOPE_H_ */
