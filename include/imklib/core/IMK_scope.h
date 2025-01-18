#ifndef IMK_SCOPE_H_ORZMLMWX2CSRKCX2
#define IMK_SCOPE_H_ORZMLMWX2CSRKCX2

#include <stdlib.h>

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_INTS

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_MACROS

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_ASSERT

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_PTR

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_MEM

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
        s_iter_2005041_++, IMK_Drop(s.ptrs[s_iter_2005041_]);)                 \
  }
#define IMK_SCOPE_RET(s, T, x)                                                 \
  {                                                                            \
    T s_ret_2005041_ = x;                                                      \
    IMK_SCOPE_END(s);                                                          \
    return s_ret_2005041_;                                                     \
  }

#ifdef USING_NAMESPACE_IMK_SCOPE
#include "IMK_index_ref.slug"
#include SLUG_IMK_ATTACH_SCOPE
#endif /* USING_NAMESPACE_IMK_SCOPE */

#endif /* !IMK_SCOPE_H_ORZMLMWX2CSRKCX2 */
