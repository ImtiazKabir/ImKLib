#ifndef IMK_OPTION_H_FW630PAIVSA45CAX
#define IMK_OPTION_H_FW630PAIVSA45CAX

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_BASE

#include "IMK_index_ref.slug"
#include SLUG_IMK_HEADER_PTR

#include "IMK_index_ref.slug"
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
#include "IMK_index_ref.slug"
#include SLUG_IMK_ATTACH_OPTION
#endif /* USING_NAMESPACE_IMK_OPTION */

#endif /* !IMK_OPTION_H_FW630PAIVSA45CAX */
