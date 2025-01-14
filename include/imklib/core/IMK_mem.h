#ifndef IMKLIB_CORE_IMK_MEM_H_
#define IMKLIB_CORE_IMK_MEM_H_

#include <stddef.h>

#include "IMK_klass.h"
#include "IMK_ptr.h"
#include "IMK_steap.h"
#include "../optres/IMK_option.h"

/*
 * BlockHeader
 * -----------------
 *                  +---------------------+
 *     base addr -> |       allockey      |
 *                  +---------------------+
 *                  |      hint/klass     |
 *                  +---------------------+
 *                  | size of client data |
 *                  +---------------------+
 *   client addr -> |          .          |
 *                  |          .          |
 *                  |          .          |
 *                  +---------------------+
 *
 * allockey is used to indicate what kind of data it is
 * if it is 314159265, it is an IMK_Klass instance
 * else if it is 271828182, it is a regular data
 */

#define IMK_KLASS_ALLOC_KEY 314159265u
#define IMK_DATA_ALLOC_KEY 271828182u

typedef struct {
  union {
    char const *hint;
    IMK_Klass *klass;
  } type;
  size_t size;
  size_t allockey;
} IMK_BlockHeader;

IMK_OptPtr IMK_VanillaAlloc(void *stack, size_t n, IMK_SteapMode mode);
IMK_OptPtr IMK_TypedAlloc(char const *type_hint, void *stack, size_t n, IMK_SteapMode mode);
IMK_Ptr IMK_VanillaAllocP(void *stack, size_t n, IMK_SteapMode mode);
IMK_Ptr IMK_TypedAllocP(char const *type_hint, void *stack, size_t n, IMK_SteapMode mode);
IMK_Ptr IMK_ToStr(IMK_Ptr ptr);

#ifdef USING_IMKLIB_CORE_IMK_MEM
#define KLASS_ALLOC_KEY IMK_KLASS_ALLOC_KEY
#define DATA_ALLOC_KEY IMK_DATA_ALLOC_KEY
typedef IMK_BlockHeader BlockHeader;
#define VanillaAlloc IMK_VanillaAlloc
#define VanillaAllocP IMK_VanillaAllocP
#define TypedAlloc  IMK_TypedAlloc
#define TypedAllocP IMK_TypedAllocP
#define ToStr IMK_ToStr
#endif /* USING_IMKLIB_CORE_IMK_MEM */

#endif /* !IMKLIB_CORE_IMK_MEM_H_ */

