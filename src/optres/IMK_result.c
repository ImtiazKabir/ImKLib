#include "imklib/core/IMK_ptr.h"
#include "imklib/core/IMK_mem.h"
#include "imklib/optres/IMK_result.h"

static void PtrDropR(IMK_Ptr ptr) { IMK_Drop(&ptr); }

IMK_RESULT_DEFINE(IMK_ResVoid, int, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResInt, int, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResShort, short, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResLong, long, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResFloat, float, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResDouble, double, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResChar, char, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResUInt, unsigned int, IMK_Ptr, IMK_ToStr,
                  PtrDropR)
IMK_RESULT_DEFINE(IMK_ResUShort, unsigned short, IMK_Ptr, IMK_ToStr,
                  PtrDropR)
IMK_RESULT_DEFINE(IMK_ResULong, unsigned long, IMK_Ptr, IMK_ToStr,
                  PtrDropR)
IMK_RESULT_DEFINE(IMK_ResUChar, unsigned char, IMK_Ptr, IMK_ToStr,
                  PtrDropR)
IMK_RESULT_DEFINE(IMK_ResRPtr, void *, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResPtr, IMK_Ptr, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResS8, s8, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResS16, s16, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResS32, s32, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResS64, s64, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResU8, u8, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResU16, u16, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResU32, u32, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResU64, u64, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResF32, f32, IMK_Ptr, IMK_ToStr, PtrDropR)
IMK_RESULT_DEFINE(IMK_ResF64, f64, IMK_Ptr, IMK_ToStr, PtrDropR)
