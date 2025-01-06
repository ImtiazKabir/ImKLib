#ifndef IMKLIB_CORE_IMK_STEAP_H_
#define IMKLIB_CORE_IMK_STEAP_H_

#include <stddef.h>
#include <stdlib.h>

#include "IMK_Ptr.h"

#define IMK_STACK(c)                                                           \
  struct {                                                                     \
    size_t cap;                                                                \
    ptrdiff_t off;                                                             \
    char mem[c];                                                               \
  }
#define IMK_STACK_INIT(s, c) IMK_STACK(c) s = {c, 0, {0}}

IMK_Ptr IMK_StackAlloc(void *steap, size_t n);
IMK_Ptr IMK_HeapAlloc(size_t n);
IMK_Ptr IMK_SteapAlloc(void *steap, size_t n);

#ifdef USING_IMKLIB_CORE_IMK_STEAP
#define STACK IMK_STACK
#define STACK_INIT IMK_STACK_INIT
#define StackAlloc IMK_StackAlloc
#define HeapAlloc IMK_HeapAlloc
#define SteapAlloc IMK_SteapAlloc
#endif /* USING_IMKLIB_CORE_IMK_STEAP */

#endif /* !IMKLIB_CORE_IMK_STEAP_H_*/
