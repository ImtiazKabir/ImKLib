#ifndef IMKLIB_BASE_IMK_FLOATS_H_
#define IMKLIB_BASE_IMK_FLOATS_H_

#include <float.h>

/* Define 32-bit floating point type (f32) */
typedef float f32;
#define F32_MIN FLT_MIN
#define F32_MAX FLT_MAX
#define F32_EPSILON FLT_EPSILON
#define F32_FMT "f"
#define F32(value) ((f32)(value))

/* Define 64-bit floating point type (f64) */
typedef double f64;
#define F64_MIN DBL_MIN
#define F64_MAX DBL_MAX
#define F64_EPSILON DBL_EPSILON
#define F64_FMT "f"
#define F64(value) ((f64)(value))

#endif /* !IMKLIB_BASE_IMK_FLOATS_H_ */
