#ifndef IMK_STEAP_H_QHOLX0YMUK6XYCF8
#define IMK_STEAP_H_QHOLX0YMUK6XYCF8

#include <stddef.h>
#include <stdlib.h>

#include "IMK_slug_index_ref.h"
#include SLUG_IMK_HEADER_PTR

#define IMK_STACK(c)                                                           \
  struct {                                                                     \
    size_t cap;                                                                \
    ptrdiff_t off;                                                             \
    char mem[c];                                                               \
  }
#define IMK_STACK_INIT(s, c) IMK_STACK(c) s = {c, 0, {0}}

typedef enum {
  IMK_PREFER_STACK,
  IMK_FORCE_STACK,
  IMK_PREFER_HEAP,
  IMK_FORCE_HEAP
} IMK_SteapMode;

#ifdef USING_NAMESPACE_IMK_STEAP
#define STACK IMK_STACK
#define STACK_INIT IMK_STACK_INIT
#define PREFER_STACK IMK_PREFER_STACK
#define FORCE_STACK IMK_FORCE_STACK
#define PREFER_HEAP IMK_PREFER_HEAP
#define FORCE_HEAP IMK_FORCE_HEAP
#define SteapMode IMK_SteapMode
#endif /* USING_NAMESPACE_IMK_STEAP */

#endif /* !IMK_STEAP_H_QHOLX0YMUK6XYCF8 */
