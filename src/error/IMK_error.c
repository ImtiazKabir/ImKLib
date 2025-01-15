#define USING_IMKLIB_ERROR_IMK_ERROR
#define USING_IMKLIB_CORE_IMK_PTR
#define USING_IMKLIB_CORE_IMK_MEM
#define USING_IMKLIB_CORE_IMK_STEAP
#define USING_IMKLIB_OPTRES_IMK_RESULT
#define USING_IMKLIB_IO_IMK_ASSERT
#define USING_IMKLIB_CORE_IMK_PARAMS

#include <string.h>

#include "imklib/error/IMK_error.h"
#include "imklib/core/IMK_ptr.h"
#include "imklib/core/IMK_mem.h"
#include "imklib/core/IMK_steap.h"
#include "imklib/core/IMK_params.h"
#include "imklib/optres/IMK_result.h"
#include "imklib/io/IMK_assert.h"

static ResVoid Error_Constructor(void *self_, Params *args) {
  Error *self = self_;
  int code;
  char *desc;
  void *stack;
  u32 mode;
  if (!ParamsMatch(args, U32(4), PARAM_INT, PARAM_RPTR, PARAM_RPTR, PARAM_U32)) {
    PanicBox("Parameter mismatch: IMK_Error::Constructor(int, void *, void *, u32)");
  }
  ParamsExtract(args, &code, &desc, &stack, &mode);

  self->code = code;
  self->desc = TypedAllocP("String", stack, strlen(desc) + 1, mode);
  strcat(self->desc.raw, desc);

  return ResVoid_Ok(0);
}

static void Error_Destructor(void *self_) {
  Error *self = self_;
  Drop(&self->desc);
}

static Ptr Error_ToStr(void const *self_, void *stack, SteapMode mode) {
  Error const *self = self_;
  Ptr ptr = TypedAllocP("String", stack, strlen(self->desc.raw) + 1, mode);
  strcat(ptr.raw, self->desc.raw);
  return PtrMove(&ptr);
}

KLASS(IMK_ErrorKlass) {
  IMK_ErrorKlass_.size = sizeof(Error);
  IMK_ErrorKlass_.ctor = Error_Constructor;
  IMK_ErrorKlass_.dtor = Error_Destructor;
  IMK_ErrorKlass_.to_str = Error_ToStr;
}


