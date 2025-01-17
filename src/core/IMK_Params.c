#include <stdarg.h>
#include <string.h>

#define USING_NAMESPACE_IMK_PARAMS
#define USING_NAMESPACE_IMK_PTR

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_slug_index_ref.h"

#include SLUG_IMK_HEADER_PARAMS
#include SLUG_IMK_HEADER_PTR
#include SLUG_IMK_HEADER_BASE

Params *ParamsVPush(Params *self, size_t len, va_list list) {
  size_t i = 0u;

  if (self == NULL) {
    return NULL;
  }
  if (self->len + len >= ARRAY_COUNT(self->params)) {
    return NULL;
  }

  for (i = 0u; i < len; i += 1u) {
    ParamType type = 0;
    self->len += 1u;

    type = va_arg(list, unsigned);
    self->params[self->len - 1u].type = type;
    switch (type) {
    case PARAM_INT:
      self->params[self->len - 1u].value.int_rep = va_arg(list, int);
      break;

    case PARAM_SHORT:
      self->params[self->len - 1u].value.short_rep = va_arg(list, int);
      break;

    case PARAM_LONG:
      self->params[self->len - 1u].value.long_rep = va_arg(list, long);
      break;

    case PARAM_FLOAT:
      self->params[self->len - 1u].value.float_rep = va_arg(list, double);
      break;

    case PARAM_DOUBLE:
      self->params[self->len - 1u].value.double_rep = va_arg(list, double);
      break;

    case PARAM_CHAR:
      self->params[self->len - 1u].value.char_rep = va_arg(list, int);
      break;

    case PARAM_UINT:
      self->params[self->len - 1u].value.uint_rep = va_arg(list, unsigned);
      break;

    case PARAM_USHORT:
      self->params[self->len - 1u].value.ushort_rep = va_arg(list, unsigned);
      break;

    case PARAM_ULONG:
      self->params[self->len - 1u].value.ulong_rep =
          va_arg(list, unsigned long);
      break;

    case PARAM_UCHAR:
      self->params[self->len - 1u].value.uchar_rep = va_arg(list, unsigned);
      break;

    case PARAM_RPTR:
      self->params[self->len - 1u].value.rptr_rep = va_arg(list, void *);
      break;

    case PARAM_PTR:
      self->params[self->len - 1u].value.ptr_rep = va_arg(list, Ptr);
      break;

    case PARAM_S8:
      self->params[self->len - 1u].value.s8_rep = va_arg(list, s32);
      break;

    case PARAM_S16:
      self->params[self->len - 1u].value.s16_rep = va_arg(list, s32);
      break;

    case PARAM_S32:
      self->params[self->len - 1u].value.s32_rep = va_arg(list, s32);
      break;

    case PARAM_S64:
      self->params[self->len - 1u].value.s64_rep = va_arg(list, s64);
      break;

    case PARAM_U8:
      self->params[self->len - 1u].value.u8_rep = va_arg(list, u32);
      break;

    case PARAM_U16:
      self->params[self->len - 1u].value.u16_rep = va_arg(list, u32);
      break;

    case PARAM_U32:
      self->params[self->len - 1u].value.u32_rep = va_arg(list, u32);
      break;

    case PARAM_U64:
      self->params[self->len - 1u].value.u64_rep = va_arg(list, u64);
      break;

    case PARAM_F32:
      self->params[self->len - 1u].value.f32_rep = va_arg(list, f64);
      break;

    case PARAM_F64:
      self->params[self->len - 1u].value.f64_rep = va_arg(list, f64);
      break;
    }
  }
  return self;
}

Params *ParamsPush(Params *self, size_t len, ...) {
  va_list list = {0};
  Params *ret = NULL;
  va_start(list, len);
  ret = ParamsVPush(self, len, list);
  va_end(list);
  return ret;
}

int ParamsMatch(Params const *self, size_t len, ...) {
  va_list list = {0};

  if (self->len != len) {
    return FALSE;
  }

  va_start(list, len);

  FOR(size_t i, i = 0u; i < len; i += 1u, {
    ParamType type = va_arg(list, ParamType);
    if (self->params[i].type != type) {
      va_end(list);
      return FALSE;
    }
  })

  va_end(list);
  return TRUE;
}

void ParamsExtract(Params const *self, ...) {
  auto va_list list = {0};
  va_start(list, self);
  FOR(size_t i, i = 0u; i < self->len; i += 1u, {
    void *ptr = va_arg(list, void *);
    ParamType type = self->params[i].type;
    switch (type) {
    case PARAM_INT:
      *(int *)ptr = self->params[i].value.int_rep;
      break;

    case PARAM_SHORT:
      *(short *)ptr = self->params[i].value.short_rep;
      break;

    case PARAM_LONG:
      *(long *)ptr = self->params[i].value.long_rep;
      break;

    case PARAM_FLOAT:
      *(float *)ptr = self->params[i].value.float_rep;
      break;

    case PARAM_DOUBLE:
      *(double *)ptr = self->params[i].value.double_rep;
      break;

    case PARAM_CHAR:
      *(char *)ptr = self->params[i].value.char_rep;
      break;

    case PARAM_UINT:
      *(unsigned int *)ptr = self->params[i].value.uint_rep;
      break;

    case PARAM_USHORT:
      *(unsigned short *)ptr = self->params[i].value.ushort_rep;
      break;

    case PARAM_ULONG:
      *(unsigned long *)ptr = self->params[i].value.ulong_rep;
      break;

    case PARAM_UCHAR:
      *(unsigned char *)ptr = self->params[i].value.uchar_rep;
      break;

    case PARAM_RPTR:
      *(void **)ptr = self->params[i].value.rptr_rep;
      break;

    case PARAM_PTR:
      *(Ptr *)ptr = self->params[i].value.ptr_rep;
      break;

    case PARAM_S8:
      *(s8 *)ptr = self->params[i].value.s8_rep;
      break;

    case PARAM_S16:
      *(s16 *)ptr = self->params[i].value.s16_rep;
      break;

    case PARAM_S32:
      *(s32 *)ptr = self->params[i].value.s32_rep;
      break;

    case PARAM_S64:
      *(s64 *)ptr = self->params[i].value.s64_rep;
      break;

    case PARAM_U8:
      *(u8 *)ptr = self->params[i].value.u8_rep;
      break;

    case PARAM_U16:
      *(u16 *)ptr = self->params[i].value.u16_rep;
      break;

    case PARAM_U32:
      *(u32 *)ptr = self->params[i].value.u32_rep;
      break;

    case PARAM_U64:
      *(u64 *)ptr = self->params[i].value.u64_rep;
      break;

    case PARAM_F32:
      *(f32 *)ptr = self->params[i].value.f32_rep;
      break;

    case PARAM_F64:
      *(f64 *)ptr = self->params[i].value.f64_rep;
      break;
    }
  })
}

void ParamsCopy(Params *dest, Params const *src) {
  memcpy(dest, src, sizeof(*dest));
}
