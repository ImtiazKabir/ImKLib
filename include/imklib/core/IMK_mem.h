#ifndef IMKLIB_CORE_IMK_MEM_H_
#define IMKLIB_CORE_IMK_MEM_H_

#include <stddef.h>

#include "IMK_ptr.h"
#include "IMK_steap.h"
#include "../optres/IMK_option.h"
#include "../optres/IMK_result.h"
#include "IMK_params.h"

#define IMK_KLASS_ALLOC_KEY 314159265u
#define IMK_DATA_ALLOC_KEY 271828182u

typedef struct IMK_Klass IMK_Klass;

struct IMK_Klass {
  void (*klass_init)(void);
  char const *const type;
  size_t size;

  IMK_Klass *super_klass;
  IMK_ResVoid (*super_params)(IMK_Params *sup_args, IMK_Params *self_args);

  IMK_ResVoid (*ctor)(void *self, IMK_Params *args);

  /*************************** rule of three *********************************/
  void (*dtor)(void *self);
  void (*clone)(void *self, void const *from);
  void (*assign)(void *self, void const *from);
  /***************************************************************************/

  size_t (*hash)(void const *self);
  int (*compare)(void const *a, void const *b);
  IMK_Ptr (*to_str)(void const *self, void *stack, IMK_SteapMode mode);

  void (*impl_of)(void *interface);
};

#define IMK_KLASS(k)                                                           \
  void GLUE(k, _Init_)(void);                                                        \
  static IMK_Klass GLUE(k, _) = {GLUE(k, _Init_),                                        \
                                "IMK_KLASS(" STRINGIFY(k) ")",                           \
                                0u,                                            \
                                NULL,                                          \
                                NULL,                                          \
                                NULL,                                          \
                                NULL,                                          \
                                NULL,                                          \
                                NULL,                                          \
                                NULL,                                          \
                                NULL,                                          \
                                NULL,                                          \
                                NULL};                                         \
  IMK_Klass *const k = &GLUE(k, _);                                                  \
  void GLUE(k, _Init_)(void)

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

typedef struct {
  union {
    char const *hint;
    IMK_Klass *klass;
  } type;
  size_t size;
  size_t allockey;
} IMK_BlockHeader;

IMK_OptPtr IMK_VanillaAlloc(void *stack, size_t n, IMK_SteapMode mode);
IMK_Ptr IMK_VanillaAllocP(void *stack, size_t n, IMK_SteapMode mode);

IMK_OptPtr IMK_TypedAlloc(char const *type_hint, void *stack, size_t n, IMK_SteapMode mode);
IMK_Ptr IMK_TypedAllocP(char const *type_hint, void *stack, size_t n, IMK_SteapMode mode);

IMK_ResPtr IMK_KlassAlloc(IMK_Klass *klass, void *stack, IMK_SteapMode mode, ...);
IMK_Ptr IMK_KlassAllocP(IMK_Klass *klass, void *stack, IMK_SteapMode mode, ...);

char const *IMK_GetTypeHint(IMK_Ptr ptr_b);
IMK_Klass *IMK_GetKlass(IMK_Ptr ptr_b);
int IMK_IsOf(IMK_Ptr ptr_b, IMK_Klass *klass);

IMK_OptPtr IMK_ToStr(IMK_Ptr ptr_b, void *stack, IMK_SteapMode mode);
IMK_Ptr IMK_ToStrP(IMK_Ptr ptr_b, void *stack, IMK_SteapMode mode);

size_t IMK_Hash(IMK_Ptr ptr_b);
int IMK_Compare(IMK_Ptr p1_b, IMK_Ptr p2_b);

IMK_OptPtr IMK_Clone(IMK_Ptr ptr_b, void *stack, IMK_SteapMode mode);
IMK_Ptr IMK_CloneP(IMK_Ptr ptr_b, void *stack, IMK_SteapMode mode);

void IMK_Assign(IMK_Ptr to_b, IMK_Ptr from_b);

#ifdef USING_IMKLIB_CORE_IMK_MEM

#define KLASS_ALLOC_KEY IMK_KLASS_ALLOC_KEY
#define DATA_ALLOC_KEY IMK_DATA_ALLOC_KEY

typedef IMK_Klass Klass;
typedef IMK_BlockHeader BlockHeader;

#define KLASS IMK_KLASS

#define VanillaAlloc IMK_VanillaAlloc
#define VanillaAllocP IMK_VanillaAllocP

#define TypedAlloc  IMK_TypedAlloc
#define TypedAllocP IMK_TypedAllocP

#define KlassAlloc IMK_KlassAlloc
#define KlassAllocP IMK_KlassAllocP

#define GetTypeHint IMK_GetTypeHint
#define GetClass IMK_GetClass

#define GetSuperKlass IMK_GetSuperKlass
#define IsOf IMK_IsOf

#define ToStr IMK_ToStr
#define ToStrP IMK_ToStrP

#define Hash IMK_Hash
#define Compare IMK_Compare

#define Clone IMK_Clone
#define CloneP IMK_CloneP
#define Assign IMK_Assign
#endif /* USING_IMKLIB_CORE_IMK_MEM */

#endif /* !IMKLIB_CORE_IMK_MEM_H_ */

