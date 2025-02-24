#ifndef IMK_PARAMS_H_EICI0XBGGZZ35SML
#define IMK_PARAMS_H_EICI0XBGGZZ35SML

#include <stdarg.h>
#include <stddef.h>

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_BASE

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_PTR

typedef enum {
  IMK_PARAM_INT,
  IMK_PARAM_SHORT,
  IMK_PARAM_LONG,
  IMK_PARAM_FLOAT,
  IMK_PARAM_DOUBLE,
  IMK_PARAM_CHAR,
  IMK_PARAM_UINT,
  IMK_PARAM_USHORT,
  IMK_PARAM_ULONG,
  IMK_PARAM_UCHAR,
  IMK_PARAM_RPTR,
  IMK_PARAM_PTR,
  IMK_PARAM_U8,
  IMK_PARAM_U16,
  IMK_PARAM_U32,
  IMK_PARAM_U64,
  IMK_PARAM_S8,
  IMK_PARAM_S16,
  IMK_PARAM_S32,
  IMK_PARAM_S64,
  IMK_PARAM_F32,
  IMK_PARAM_F64
} IMK_ParamType;

typedef union {
  int int_rep;
  short short_rep;
  long long_rep;
  float float_rep;
  double double_rep;
  char char_rep;
  unsigned int uint_rep;
  unsigned short ushort_rep;
  unsigned long ulong_rep;
  unsigned char uchar_rep;
  void *rptr_rep;
  IMK_Ptr ptr_rep;
  u8 u8_rep;
  u16 u16_rep;
  u32 u32_rep;
  u64 u64_rep;
  s8 s8_rep;
  s16 s16_rep;
  s32 s32_rep;
  s64 s64_rep;
  f32 f32_rep;
  f64 f64_rep;
} IMK_ParamValue;

typedef struct {
  size_t len;
  struct {
    IMK_ParamType type;
    IMK_ParamValue value;
  } params[16];
} IMK_Params;

IMK_Params *IMK_ParamsVPush(IMK_Params *self, size_t len, va_list list);
IMK_Params *IMK_ParamsPush(IMK_Params *self, size_t len, ...);
int IMK_ParamsMatch(IMK_Params const *self, size_t len, ...);
void IMK_ParamsExtract(IMK_Params const *self, ...);
void IMK_ParamsCopy(IMK_Params *dest, IMK_Params const *src);

#ifdef USING_NAMESPACE_IMK_PARAMS
#include "IMK_index_ref.slug"
#include SLUG_IMK_ATTACH_PARAMS
#endif /* USING_NAMESPACE_IMK_PARAMS */

#endif /* !IMK_PARAMS_H_EICI0XBGGZZ35SML */
