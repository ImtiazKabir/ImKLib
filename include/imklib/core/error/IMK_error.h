#ifndef IMK_ERROR_H_O8H417O925IC46K6
#define IMK_ERROR_H_O8H417O925IC46K6

#include <string.h>

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_INTS

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_MEM

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_PARAMS

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_PTR

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_STEAP

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_ASSERT

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_RESULT

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
  IMK_KLASS(GLUE_(name, Klass)) {                                              \
    GLUE(GLUE_(name, Klass), _).size = sizeof(name);                           \
    GLUE(GLUE_(name, Klass), _).super_klass = GLUE_(parent, Klass);            \
    GLUE(GLUE_(name, Klass), _).super_params = GLUE(name, _SuperParams_);      \
    GLUE(GLUE_(name, Klass), _).to_str = GLUE(name, _ToStr_);                  \
  }

#ifdef USING_NAMESPACE_IMK_ERROR
#define Error IMK_Error
#define ErrorKlass IMK_ErrorKlass
#define ERROR_DECLARE IMK_ERROR_DECLARE
#define ERROR_DEFINE IMK_ERROR_DEFINE
#define ErrorThrow IMK_ErrorThrow
#endif /* USING_NAMESPACE_IMK_ERROR */

#endif /* !IMK_ERROR_H_O8H417O925IC46K6 */
