#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#define USING_NAMESPACE_IMK_CORE
#include SLUG_IMK_HEADER_CORE

static ResVoid Error_Constructor(Ptr self, Params *args) {
  int code;
  char *desc;
  void *stack;
  u32 mode;
  if (!ParamsMatch(args, U32(4), PARAM_INT, PARAM_RPTR, PARAM_RPTR,
                   PARAM_U32)) {
    PanicBox(
        "Parameter mismatch: IMK_Error::Constructor(int, void *, void *, u32)");
  }
  ParamsExtract(args, &code, &desc, &stack, &mode);

  PTR_DEREF(self, Error).code = code;
  PTR_DEREF(self, Error).desc =
      TypedAllocP("String", stack, strlen(desc) + 1, mode);
  strcat(PTR_DEREF(self, Error).desc.raw, desc);

  return ResVoid_Ok(0);
}

static void Error_Destructor(Ptr self) { Drop(&PTR_DEREF(self, Error).desc); }

static OptPtr Error_ToStr(Ptr self_, void *stack, SteapMode mode) {
  Error self = PTR_DEREF(self_, Error);
  char const *prefix = "[IMK_Error]: ";
  OptPtr opt = TypedAlloc("String", stack,
                        strlen(prefix) + strlen(self.desc.raw) + 1, mode);
  Ptr ptr;
  OPTION_TRY(ptr, OptPtr, opt, OptPtr);
  strcat(ptr.raw, prefix);
  strcat(ptr.raw, self.desc.raw);
  return OptPtr_Some(PtrMove(&ptr));
}

void ErrorThrow(Ptr self, void *stack, SteapMode mode) {
  char const *prefix = "Thrown ";
  Ptr str = ToStrP(self, stack, mode);
  Ptr msg =
      TypedAllocP("String", stack, strlen(prefix) + strlen(str.raw) + 1, mode);
  strcat(msg.raw, prefix);
  strcat(msg.raw, str.raw);
  Drop(&str);
  PanicBox(msg.raw);
  Drop(&msg);
}

KLASS(IMK_ErrorKlass) {
  IMK_ErrorKlass_.size = sizeof(Error);
  IMK_ErrorKlass_.ctor = Error_Constructor;
  IMK_ErrorKlass_.dtor = Error_Destructor;
  IMK_ErrorKlass_.to_str = Error_ToStr;
}
