#ifndef IMKLIB_BASE_IMK_BOOL_H_
#define IMKLIB_BASE_IMK_BOOL_H_

#include "IMK_slug_index_ref.h"
#include IMK_SLUG_INTS

#define FALSE U8(0)
#define TRUE U8(1)

#define BOOLIFY(x) ((x) != FALSE)

#endif /* !IMKLIB_BASE_IMK_BOOL_H_ */
