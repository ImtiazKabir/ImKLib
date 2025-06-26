#ifndef IMK_STEAP_H_QHOLX0YMUK6XYCF8
#define IMK_STEAP_H_QHOLX0YMUK6XYCF8

#include <stddef.h>
#include <stdlib.h>

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_PTR
#include SLUG_IMK_HEADER_BASE

#define IMK_STACK(c)                                                           \
  struct {                                                                     \
    size_t cap;                                                                \
    ptrdiff_t off;                                                             \
    char mem[c];                                                               \
  }
#define IMK_STACK_INIT(s, c) IMK_STACK(c) s = {c, 0, {0}}
#define IMK_STACK_CLEAR(s) STATEMENT(s.cap = sizeof(s.mem); s.off = 0;)

typedef enum {
  IMK_PREFER_STACK,
  IMK_FORCE_STACK,
  IMK_PREFER_HEAP,
  IMK_FORCE_HEAP
} IMK_SteapMode;

#ifdef USING_NAMESPACE_IMK_STEAP
#include "IMK_index_ref.slug"
#include SLUG_IMK_ATTACH_STEAP
#endif /* USING_NAMESPACE_IMK_STEAP */

#endif /* !IMK_STEAP_H_QHOLX0YMUK6XYCF8 */
