#define IMK_SLUG_EXTERN_ROOT_DIR imklib
#include "imklib/IMK_slug_index_ref.h"

#include IMK_SLUG_RESULT
#include IMK_SLUG_PTR
#include IMK_SLUG_MEM

static void PtrDropR(IMK_Ptr ptr) { IMK_Drop(&ptr); }
static IMK_Ptr PtrToStrR(IMK_Ptr ptr) {
  return IMK_ToStrP(ptr, NULL, IMK_FORCE_HEAP);
}

IMK_RESULT_DEFINE(IMK_ResVoid, int, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResInt, int, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResShort, short, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResLong, long, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResFloat, float, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResDouble, double, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResChar, char, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResUInt, unsigned int, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResUShort, unsigned short, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResULong, unsigned long, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResUChar, unsigned char, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResRPtr, void *, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResPtr, IMK_Ptr, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResS8, s8, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResS16, s16, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResS32, s32, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResS64, s64, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResU8, u8, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResU16, u16, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResU32, u32, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResU64, u64, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResF32, f32, IMK_Ptr, PtrToStrR, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResF64, f64, IMK_Ptr, PtrToStrR, PtrDropR)
