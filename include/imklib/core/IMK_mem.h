#ifndef IMK_MEM_H_2JH5L1VYK3BJSRZ9
#define IMK_MEM_H_2JH5L1VYK3BJSRZ9

#include <stddef.h>

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_PTR

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_STEAP

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_OPTION

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_RESULT

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_PARAMS

#define IMK_KLASS_ALLOC_KEY 314159265u
#define IMK_DATA_ALLOC_KEY 271828182u

typedef struct IMK_Klass IMK_Klass;

struct IMK_Klass {
  void (*klass_init)(void);
  char const *const type;
  size_t size;

  IMK_Klass *super_klass;
  IMK_ResVoid (*super_params)(IMK_Params *sup_args, IMK_Params *self_args);

  IMK_ResVoid (*ctor)(IMK_Ptr self, IMK_Params *args);

  /*************************** rule of three *********************************/
  void (*dtor)(IMK_Ptr ptr);
  void (*clone)(IMK_Ptr self, IMK_Ptr from);
  void (*assign)(IMK_Ptr self, IMK_Ptr from);
  /***************************************************************************/

  size_t (*hash)(IMK_Ptr self);
  int (*compare)(IMK_Ptr a, IMK_Ptr b);
  IMK_Ptr (*to_str)(IMK_Ptr self, void *stack, IMK_SteapMode mode);

  void (*impl_filler)(IMK_Ptr interface);
};

#define IMK_KLASS(k)                                                           \
  void GLUE(k, _Init_)(void);                                                  \
  static IMK_Klass GLUE(k, _) = {GLUE(k, _Init_),                              \
                                 "IMK_KLASS(" STRINGIFY(k) ")",                \
                                 0u,                                           \
                                 NULL,                                         \
                                 NULL,                                         \
                                 NULL,                                         \
                                 NULL,                                         \
                                 NULL,                                         \
                                 NULL,                                         \
                                 NULL,                                         \
                                 NULL,                                         \
                                 NULL,                                         \
                                 NULL};                                        \
  IMK_Klass *const k = &GLUE(k, _);                                            \
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

IMK_OptPtr IMK_TypedAlloc(char const *type_hint, void *stack, size_t n,
                          IMK_SteapMode mode);
IMK_Ptr IMK_TypedAllocP(char const *type_hint, void *stack, size_t n,
                        IMK_SteapMode mode);

IMK_ResPtr IMK_KlassAlloc(IMK_Klass *klass, void *stack, IMK_SteapMode mode,
                          ...);
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

IMK_ResPtr IMK_GetImplOf(IMK_Klass *implementation, IMK_Klass *interface, void *stack, IMK_SteapMode mode);
IMK_Ptr IMK_GetImplOfP(IMK_Klass *implementation, IMK_Klass *interface, void *stack, IMK_SteapMode mode);

#ifdef USING_NAMESPACE_IMK_MEM
#include "IMK_index_ref.slug"
#include SLUG_IMK_ATTACH_MEM
#endif /* USING_NAMESPACE_IMK_MEM */

#endif /* !IMK_MEM_H_2JH5L1VYK3BJSRZ9 */
