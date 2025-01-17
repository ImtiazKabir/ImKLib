#ifndef IMK_OPTION_H_FW630PAIVSA45CAX
#define IMK_OPTION_H_FW630PAIVSA45CAX

#include "IMK_slug_index_ref.h"
#include SLUG_IMK_HEADER_BASE

#include "IMK_slug_index_ref.h"
#include SLUG_IMK_HEADER_PTR

#include "IMK_slug_index_ref.h"
#include SLUG_IMK_HEADER_ASSERT

#define IMK_OPTION_SOME(opt) GLUE(opt, _Some)
#define IMK_OPTION_NONE(opt) GLUE(opt, _None)
#define IMK_OPTION_IS_SOME(opt) GLUE(opt, _IsSome)
#define IMK_OPTION_IS_NONE(opt) GLUE(opt, _IsNone)
#define IMK_OPTION_UNWRAP(opt) GLUE(opt, _Unwrap)
#define IMK_OPTION_EXPECT(opt) GLUE(opt, _Expect)
#define IMK_OPTION_UNWRAP_OR(opt) GLUE(opt, _UnwrapOr)

#define IMK_OPTION_DECLARE(O, T)                                               \
  struct O {                                                                   \
    T value;                                                                   \
    u8 some;                                                                   \
  };                                                                           \
  struct O IMK_OPTION_SOME(O)(T);                                              \
  struct O IMK_OPTION_NONE(O)(void);                                           \
  int IMK_OPTION_IS_SOME(O)(struct O);                                         \
  int IMK_OPTION_IS_NONE(O)(struct O);                                         \
  T IMK_OPTION_UNWRAP(O)(struct O);                                            \
  T IMK_OPTION_EXPECT(O)(struct O, char const *);                              \
  T IMK_OPTION_UNWRAP_OR(O)(struct O, T);

#define IMK_OPTION_DEFINE(O, T)                                                \
  struct O IMK_OPTION_SOME(O)(T value) {                                       \
    struct O opt = {0};                                                        \
    opt.value = value;                                                         \
    opt.some = 1;                                                              \
    return opt;                                                                \
  }                                                                            \
  struct O IMK_OPTION_NONE(O)(void) {                                          \
    struct O opt = {0};                                                        \
    opt.some = 0;                                                              \
    return opt;                                                                \
  }                                                                            \
  int IMK_OPTION_IS_SOME(O)(struct O opt) { return opt.some != 0; }            \
  int IMK_OPTION_IS_NONE(O)(struct O opt) { return opt.some == 0; }            \
  T IMK_OPTION_UNWRAP(O)(struct O opt) {                                       \
    IMK_ASSERT_MSG(IMK_OPTION_IS_SOME(O)(opt),                                 \
                   "Attempted to unwrap empty Option of type " #T);            \
    return opt.value;                                                          \
  }                                                                            \
  T IMK_OPTION_EXPECT(O)(struct O opt, char const *message_on_none) {          \
    IMK_ASSERT_MSG(IMK_OPTION_IS_SOME(O)(opt), message_on_none);               \
    return opt.value;                                                          \
  }                                                                            \
  T IMK_OPTION_UNWRAP_OR(O)(struct O opt, T else_val) {                        \
    if (IMK_OPTION_IS_NONE(O)(opt)) {                                          \
      return else_val;                                                         \
    }                                                                          \
    return opt.value;                                                          \
  }

#define IMK_OPTION_TRY(dest, O, opt, R)                                        \
  do {                                                                         \
    O UNIQUE_NAME(GLUE(GLUE(option_, O), _try_at)) = opt;                      \
    if (UNIQUE_NAME(GLUE(GLUE(option_, O), _try_at)).some == 0) {              \
      return IMK_OPTION_NONE(R)();                                             \
    }                                                                          \
    dest = UNIQUE_NAME(GLUE(GLUE(option_, O), _try_at)).value;                 \
  } while (0)

IMK_OPTION_DECLARE(IMK_OptVoid, int)
IMK_OPTION_DECLARE(IMK_OptInt, int)
IMK_OPTION_DECLARE(IMK_OptShort, short)
IMK_OPTION_DECLARE(IMK_OptLong, long)
IMK_OPTION_DECLARE(IMK_OptFloat, float)
IMK_OPTION_DECLARE(IMK_OptDouble, double)
IMK_OPTION_DECLARE(IMK_OptChar, char)
IMK_OPTION_DECLARE(IMK_OptUInt, unsigned int)
IMK_OPTION_DECLARE(IMK_OptUShort, unsigned short)
IMK_OPTION_DECLARE(IMK_OptULong, unsigned long)
IMK_OPTION_DECLARE(IMK_OptUChar, unsigned char)
IMK_OPTION_DECLARE(IMK_OptRPtr, void *)
IMK_OPTION_DECLARE(IMK_OptPtr, IMK_Ptr)
IMK_OPTION_DECLARE(IMK_OptS8, s8)
IMK_OPTION_DECLARE(IMK_OptS16, s16)
IMK_OPTION_DECLARE(IMK_OptS32, s32)
IMK_OPTION_DECLARE(IMK_OptS64, s64)
IMK_OPTION_DECLARE(IMK_OptU8, u8)
IMK_OPTION_DECLARE(IMK_OptU16, u16)
IMK_OPTION_DECLARE(IMK_OptU32, u32)
IMK_OPTION_DECLARE(IMK_OptU64, u64)
IMK_OPTION_DECLARE(IMK_OptF32, f32)
IMK_OPTION_DECLARE(IMK_OptF64, f64)

typedef struct IMK_OptVoid IMK_OptVoid;
typedef struct IMK_OptInt IMK_OptInt;
typedef struct IMK_OptShort IMK_OptShort;
typedef struct IMK_OptLong IMK_OptLong;
typedef struct IMK_OptFloat IMK_OptFloat;
typedef struct IMK_OptDouble IMK_OptDouble;
typedef struct IMK_OptChar IMK_OptChar;
typedef struct IMK_OptUInt IMK_OptUInt;
typedef struct IMK_OptUShort IMK_OptUShort;
typedef struct IMK_OptULong IMK_OptULong;
typedef struct IMK_OptUChar IMK_OptUChar;
typedef struct IMK_OptRPtr IMK_OptRPtr;
typedef struct IMK_OptPtr IMK_OptPtr;
typedef struct IMK_OptS8 IMK_OptS8;
typedef struct IMK_OptS16 IMK_OptS16;
typedef struct IMK_OptS32 IMK_OptS32;
typedef struct IMK_OptS64 IMK_OptS64;
typedef struct IMK_OptU8 IMK_OptU8;
typedef struct IMK_OptU16 IMK_OptU16;
typedef struct IMK_OptU32 IMK_OptU32;
typedef struct IMK_OptU64 IMK_OptU64;
typedef struct IMK_OptF32 IMK_OptF32;
typedef struct IMK_OptF64 IMK_OptF64;

#ifdef USING_NAMESPACE_IMK_OPTION
#define OPTION_SOME IMK_OPTION_SOME
#define OPTION_NONE IMK_OPTION_NONE
#define OPTION_IS_SOME IMK_OPTION_IS_SOME
#define OPTION_IS_NONE IMK_OPTION_IS_NONE
#define OPTION_UNWRAP IMK_OPTION_UNWRAP
#define OPTION_EXPECT IMK_OPTION_EXPECT
#define OPTION_UNWRAP_OR IMK_OPTION_UNWRAP_OR
#define OPTION_TRY IMK_OPTION_TRY

#define OPTION_DECLARE IMK_OPTION_DECLARE
#define OPTION_DEFINE IMK_OPTION_DEFINE

typedef IMK_OptVoid OptVoid;
typedef IMK_OptInt OptInt;
typedef IMK_OptShort OptShort;
typedef IMK_OptLong OptLong;
typedef IMK_OptFloat OptFloat;
typedef IMK_OptDouble OptDouble;
typedef IMK_OptChar OptChar;
typedef IMK_OptUInt OptUInt;
typedef IMK_OptUShort OptUShort;
typedef IMK_OptULong OptULong;
typedef IMK_OptUChar OptUChar;
typedef IMK_OptRPtr OptRPtr;
typedef IMK_OptPtr OptPtr;
typedef IMK_OptS8 OptS8;
typedef IMK_OptS16 OptS16;
typedef IMK_OptS32 OptS32;
typedef IMK_OptS64 OptS64;
typedef IMK_OptU8 OptU8;
typedef IMK_OptU16 OptU16;
typedef IMK_OptU32 OptU32;
typedef IMK_OptU64 OptU64;
typedef IMK_OptF32 OptF32;
typedef IMK_OptF64 OptF64;

#define OptVoid_Some IMK_OptVoid_Some
#define OptVoid_None IMK_OptVoid_None
#define OptVoid_IsSome IMK_OptVoid_IsSome
#define OptVoid_IsNone IMK_OptVoid_IsNone
#define OptVoid_Unwrap IMK_OptVoid_Unwrap
#define OptVoid_Expect IMK_OptVoid_Expect
#define OptVoid_UnwrapOr IMK_OptVoid_UnwrapOr

#define OptInt_Some IMK_OptInt_Some
#define OptInt_None IMK_OptInt_None
#define OptInt_IsSome IMK_OptInt_IsSome
#define OptInt_IsNone IMK_OptInt_IsNone
#define OptInt_Unwrap IMK_OptInt_Unwrap
#define OptInt_Expect IMK_OptInt_Expect
#define OptInt_UnwrapOr IMK_OptInt_UnwrapOr

#define OptShort_Some IMK_OptShort_Some
#define OptShort_None IMK_OptShort_None
#define OptShort_IsSome IMK_OptShort_IsSome
#define OptShort_IsNone IMK_OptShort_IsNone
#define OptShort_Unwrap IMK_OptShort_Unwrap
#define OptShort_Expect IMK_OptShort_Expect
#define OptShort_UnwrapOr IMK_OptShort_UnwrapOr

#define OptLong_Some IMK_OptLong_Some
#define OptLong_None IMK_OptLong_None
#define OptLong_IsSome IMK_OptLong_IsSome
#define OptLong_IsNone IMK_OptLong_IsNone
#define OptLong_Unwrap IMK_OptLong_Unwrap
#define OptLong_Expect IMK_OptLong_Expect
#define OptLong_UnwrapOr IMK_OptLong_UnwrapOr

#define OptFloat_Some IMK_OptFloat_Some
#define OptFloat_None IMK_OptFloat_None
#define OptFloat_IsSome IMK_OptFloat_IsSome
#define OptFloat_IsNone IMK_OptFloat_IsNone
#define OptFloat_Unwrap IMK_OptFloat_Unwrap
#define OptFloat_Expect IMK_OptFloat_Expect
#define OptFloat_UnwrapOr IMK_OptFloat_UnwrapOr

#define OptDouble_Some IMK_OptDouble_Some
#define OptDouble_None IMK_OptDouble_None
#define OptDouble_IsSome IMK_OptDouble_IsSome
#define OptDouble_IsNone IMK_OptDouble_IsNone
#define OptDouble_Unwrap IMK_OptDouble_Unwrap
#define OptDouble_Expect IMK_OptDouble_Expect
#define OptDouble_UnwrapOr IMK_OptDouble_UnwrapOr

#define OptChar_Some IMK_OptChar_Some
#define OptChar_None IMK_OptChar_None
#define OptChar_IsSome IMK_OptChar_IsSome
#define OptChar_IsNone IMK_OptChar_IsNone
#define OptChar_Unwrap IMK_OptChar_Unwrap
#define OptChar_Expect IMK_OptChar_Expect
#define OptChar_UnwrapOr IMK_OptChar_UnwrapOr

#define OptUInt_Some IMK_OptUInt_Some
#define OptUInt_None IMK_OptUInt_None
#define OptUInt_IsSome IMK_OptUInt_IsSome
#define OptUInt_IsNone IMK_OptUInt_IsNone
#define OptUInt_Unwrap IMK_OptUInt_Unwrap
#define OptUInt_Expect IMK_OptUInt_Expect
#define OptUInt_UnwrapOr IMK_OptUInt_UnwrapOr

#define OptUShort_Some IMK_OptUShort_Some
#define OptUShort_None IMK_OptUShort_None
#define OptUShort_IsSome IMK_OptUShort_IsSome
#define OptUShort_IsNone IMK_OptUShort_IsNone
#define OptUShort_Unwrap IMK_OptUShort_Unwrap
#define OptUShort_Expect IMK_OptUShort_Expect
#define OptUShort_UnwrapOr IMK_OptUShort_UnwrapOr

#define OptULong_Some IMK_OptULong_Some
#define OptULong_None IMK_OptULong_None
#define OptULong_IsSome IMK_OptULong_IsSome
#define OptULong_IsNone IMK_OptULong_IsNone
#define OptULong_Unwrap IMK_OptULong_Unwrap
#define OptULong_Expect IMK_OptULong_Expect
#define OptULong_UnwrapOr IMK_OptULong_UnwrapOr

#define OptUChar_Some IMK_OptUChar_Some
#define OptUChar_None IMK_OptUChar_None
#define OptUChar_IsSome IMK_OptUChar_IsSome
#define OptUChar_IsNone IMK_OptUChar_IsNone
#define OptUChar_Unwrap IMK_OptUChar_Unwrap
#define OptUChar_Expect IMK_OptUChar_Expect
#define OptUChar_UnwrapOr IMK_OptUChar_UnwrapOr

#define OptRPtr_Some IMK_OptRPtr_Some
#define OptRPtr_None IMK_OptRPtr_None
#define OptRPtr_IsSome IMK_OptRPtr_IsSome
#define OptRPtr_IsNone IMK_OptRPtr_IsNone
#define OptRPtr_Unwrap IMK_OptRPtr_Unwrap
#define OptRPtr_Expect IMK_OptRPtr_Expect
#define OptRPtr_UnwrapOr IMK_OptRPtr_UnwrapOr

#define OptPtr_Some IMK_OptPtr_Some
#define OptPtr_None IMK_OptPtr_None
#define OptPtr_IsSome IMK_OptPtr_IsSome
#define OptPtr_IsNone IMK_OptPtr_IsNone
#define OptPtr_Unwrap IMK_OptPtr_Unwrap
#define OptPtr_Expect IMK_OptPtr_Expect
#define OptPtr_UnwrapOr IMK_OptPtr_UnwrapOr

#define OptS8_Some IMK_OptS8_Some
#define OptS8_None IMK_OptS8_None
#define OptS8_IsSome IMK_OptS8_IsSome
#define OptS8_IsNone IMK_OptS8_IsNone
#define OptS8_Unwrap IMK_OptS8_Unwrap
#define OptS8_Expect IMK_OptS8_Expect
#define OptS8_UnwrapOr IMK_OptS8_UnwrapOr

#define OptS16_Some IMK_OptS16_Some
#define OptS16_None IMK_OptS16_None
#define OptS16_IsSome IMK_OptS16_IsSome
#define OptS16_IsNone IMK_OptS16_IsNone
#define OptS16_Unwrap IMK_OptS16_Unwrap
#define OptS16_Expect IMK_OptS16_Expect
#define OptS16_UnwrapOr IMK_OptS16_UnwrapOr

#define OptS32_Some IMK_OptS32_Some
#define OptS32_None IMK_OptS32_None
#define OptS32_IsSome IMK_OptS32_IsSome
#define OptS32_IsNone IMK_OptS32_IsNone
#define OptS32_Unwrap IMK_OptS32_Unwrap
#define OptS32_Expect IMK_OptS32_Expect
#define OptS32_UnwrapOr IMK_OptS32_UnwrapOr

#define OptS64_Some IMK_OptS64_Some
#define OptS64_None IMK_OptS64_None
#define OptS64_IsSome IMK_OptS64_IsSome
#define OptS64_IsNone IMK_OptS64_IsNone
#define OptS64_Unwrap IMK_OptS64_Unwrap
#define OptS64_Expect IMK_OptS64_Expect
#define OptS64_UnwrapOr IMK_OptS64_UnwrapOr

#define OptU8_Some IMK_OptU8_Some
#define OptU8_None IMK_OptU8_None
#define OptU8_IsSome IMK_OptU8_IsSome
#define OptU8_IsNone IMK_OptU8_IsNone
#define OptU8_Unwrap IMK_OptU8_Unwrap
#define OptU8_Expect IMK_OptU8_Expect
#define OptU8_UnwrapOr IMK_OptU8_UnwrapOr

#define OptU16_Some IMK_OptU16_Some
#define OptU16_None IMK_OptU16_None
#define OptU16_IsSome IMK_OptU16_IsSome
#define OptU16_IsNone IMK_OptU16_IsNone
#define OptU16_Unwrap IMK_OptU16_Unwrap
#define OptU16_Expect IMK_OptU16_Expect
#define OptU16_UnwrapOr IMK_OptU16_UnwrapOr

#define OptU32_Some IMK_OptU32_Some
#define OptU32_None IMK_OptU32_None
#define OptU32_IsSome IMK_OptU32_IsSome
#define OptU32_IsNone IMK_OptU32_IsNone
#define OptU32_Unwrap IMK_OptU32_Unwrap
#define OptU32_Expect IMK_OptU32_Expect
#define OptU32_UnwrapOr IMK_OptU32_UnwrapOr

#define OptU64_Some IMK_OptU64_Some
#define OptU64_None IMK_OptU64_None
#define OptU64_IsSome IMK_OptU64_IsSome
#define OptU64_IsNone IMK_OptU64_IsNone
#define OptU64_Unwrap IMK_OptU64_Unwrap
#define OptU64_Expect IMK_OptU64_Expect
#define OptU64_UnwrapOr IMK_OptU64_UnwrapOr

#define OptF32_Some IMK_OptF32_Some
#define OptF32_None IMK_OptF32_None
#define OptF32_IsSome IMK_OptF32_IsSome
#define OptF32_IsNone IMK_OptF32_IsNone
#define OptF32_Unwrap IMK_OptF32_Unwrap
#define OptF32_Expect IMK_OptF32_Expect
#define OptF32_UnwrapOr IMK_OptF32_UnwrapOr

#define OptF64_Some IMK_OptF64_Some
#define OptF64_None IMK_OptF64_None
#define OptF64_IsSome IMK_OptF64_IsSome
#define OptF64_IsNone IMK_OptF64_IsNone
#define OptF64_Unwrap IMK_OptF64_Unwrap
#define OptF64_Expect IMK_OptF64_Expect
#define OptF64_UnwrapOr IMK_OptF64_UnwrapOr

#endif /* USING_NAMESPACE_IMK_OPTION */

#endif /* !IMK_OPTION_H_FW630PAIVSA45CAX */
