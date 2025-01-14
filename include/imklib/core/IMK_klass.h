#ifndef IMKLIB_CORE_IMK_KLASS_H_
#define IMKLIB_CORE_IMK_KLASS_H_

#include <stddef.h>

#include "IMK_params.h"
#include "../optres/IMK_result.h"

typedef struct IMK_Klass IMK_Klass;

struct IMK_Klass {
  void (*class_init)(void);
  char const *const type;
  size_t size;

  IMK_Klass *super_class;
  IMK_ResPtr (*super_params)(IMK_Params *sup_args, IMK_Params *self_args);

  IMK_ResPtr (*ctor)(void *self, IMK_Params *args);

  /*************************** rule of three *********************************/
  void (*dtor)(void *self);
  void (*clone)(void *self, void const *from);
  void (*assign)(void *self, void const *from);
  /***************************************************************************/

  size_t (*hash)(void const *self);
  int (*compare)(void const *a, void const *b);
  IMK_Ptr (*tostr)(void const *self);

  void (*implof)(void *interface);
  void (*cast)(void *self, IMK_Klass *to_klass, void *to);
};

#define IMK_KLASS(k)                                                           \
  void k##_Init_(void);                                                        \
  static IMK_Klass ##k_ = {##k##_Init_,                                        \
                                "IMK_KLASS(" #k ")",                           \
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
                                NULL,                                          \
                                NULL};                                         \
  IMK_Klass *const k = &##k_;                                                  \
  void ##k##_Init_(void)


#ifdef USING_IMKLIB_CORE_IMK_KLASS
#endif /* USING_IMKLIB_CORE_IMK_KLASS */

#endif /* !IMKLIB_CORE_IMK_KLASS_H_ */

