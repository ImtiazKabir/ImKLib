#ifndef IMKLIB_ERROR_IMK_ERROR_H_
#define IMKLIB_ERROR_IMK_ERROR_H_

#include <string.h>

#include "IMK_slug_index_ref.h"
#include IMK_SLUG_INTS

#include "IMK_slug_index_ref.h"
#include IMK_SLUG_MEM

#include "IMK_slug_index_ref.h"
#include IMK_SLUG_PARAMS

#include "IMK_slug_index_ref.h"
#include IMK_SLUG_PTR

#include "IMK_slug_index_ref.h"
#include IMK_SLUG_STEAP

#include "IMK_slug_index_ref.h"
#include IMK_SLUG_ASSERT

#include "IMK_slug_index_ref.h"
#include IMK_SLUG_RESULT

typedef struct {
  int code;
  IMK_Ptr desc;
} IMK_Error;

extern IMK_Klass *const IMK_ErrorKlass;

void IMK_ErrorThrow(IMK_Ptr self, void *stack, IMK_SteapMode mode);

#define IMK_ERROR_DECLARE(name, parent)                                        \
  typedef struct {                                                             \
    parent err;                                                                \
  } name;                                                                      \
  extern IMK_Klass *const GLUE(name, Klass);

#define IMK_ERROR_DEFINE(name, parent, c, d)                                   \
  static IMK_ResVoid GLUE(name, _SuperParams_)(IMK_Params * sup_args,          \
                                               IMK_Params * self_args) {       \
    if (IMK_ParamsMatch(self_args, U32(4), IMK_PARAM_INT, IMK_PARAM_RPTR,      \
                        IMK_PARAM_RPTR, IMK_PARAM_U32)) {                      \
      int arg_code = 0;                                                        \
      char const *arg_desc = NULL;                                             \
      void *stack = NULL;                                                      \
      u32 mode = 0;                                                            \
      IMK_ParamsExtract(self_args, &arg_code, &arg_desc, &stack, &mode);       \
      IMK_ParamsPush(sup_args, U32(4), IMK_PARAM_INT, arg_code,                \
                     IMK_PARAM_RPTR, arg_desc, IMK_PARAM_RPTR, stack,          \
                     IMK_PARAM_U32, mode);                                     \
    } else if (IMK_ParamsMatch(self_args, U32(3), IMK_PARAM_RPTR,              \
                               IMK_PARAM_RPTR, IMK_PARAM_U32)) {               \
      char const *arg_desc = NULL;                                             \
      void *stack = NULL;                                                      \
      u32 mode = 0;                                                            \
      IMK_ParamsExtract(self_args, &arg_desc, &stack, &mode);                  \
      IMK_ParamsPush(sup_args, U32(4), IMK_PARAM_INT, c, IMK_PARAM_RPTR,       \
                     arg_desc, IMK_PARAM_RPTR, stack, IMK_PARAM_U32, mode);    \
    } else if (IMK_ParamsMatch(self_args, U32(2), IMK_PARAM_RPTR,              \
                               IMK_PARAM_U32)) {                               \
      void *stack = NULL;                                                      \
      u32 mode = 0;                                                            \
      IMK_ParamsExtract(self_args, &stack, &mode);                             \
      IMK_ParamsPush(sup_args, U32(4), IMK_PARAM_INT, c, IMK_PARAM_RPTR, d,    \
                     IMK_PARAM_RPTR, stack, IMK_PARAM_U32, mode);              \
    } else {                                                                   \
      IMK_PanicBox("Parameter mismatch: Subklass::IMK_Error::Constructor");    \
    }                                                                          \
    return IMK_ResVoid_Ok(0);                                                  \
  }                                                                            \
  static IMK_Ptr GLUE(name, _ToStr_)(Ptr self_, void *stack,                   \
                                     IMK_SteapMode mode) {                     \
    IMK_Error self = IMK_PTR_DEREF(self_, IMK_Error);                          \
    char const *prefix = "[" STRINGIFY(name) "]: ";                            \
    IMK_Ptr ptr = IMK_TypedAllocP(                                             \
        "String", stack, strlen(prefix) + strlen(self.desc.raw) + 1, mode);    \
    strcat(ptr.raw, prefix);                                                   \
    strcat(ptr.raw, self.desc.raw);                                            \
    return IMK_PtrMove(&ptr);                                                  \
  }                                                                            \
                                                                               \
  IMK_KLASS(GLUE(name, Klass)) {                                               \
    GLUE(GLUE(name, Klass), _).size = sizeof(name);                            \
    GLUE(GLUE(name, Klass), _).super_klass = GLUE(parent, Klass);              \
    GLUE(GLUE(name, Klass), _).super_params = GLUE(name, _SuperParams_);       \
    GLUE(GLUE(name, Klass), _).to_str = GLUE(name, _ToStr_);                   \
  }

#ifdef USING_IMKLIB_ERROR_IMK_ERROR
typedef IMK_Error Error;
#define ErrorKlass IMK_ErrorKlass
#define ERROR_DECLARE IMK_ERROR_DECLARE
#define ERROR_DEFINE IMK_ERROR_DEFINE
#define ErrorThrow IMK_ErrorThrow
#endif /* USING_IMKLIB_ERROR_IMK_ERROR */

#endif /* !IMKLIB_ERROR_IMK_ERROR_H_ */
