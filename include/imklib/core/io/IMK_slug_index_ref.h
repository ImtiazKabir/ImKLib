/* clang-format off */
#ifdef IMK_SLUG_EXTERN_ROOT_DIR
#define IMK_SLUG_ROOT_DIR IMK_SLUG_EXTERN_ROOT_DIR
#else
#include "IMK_slug_root_ref.h"
#endif

#ifndef IMK_SLUG_STRINGIFY
#define IMK_SLUG_XSTRINGIFY(x) #x
#define IMK_SLUG_STRINGIFY(x) IMK_SLUG_XSTRINGIFY(x)
#endif /* IMK_SLUG_STRINGIFY */

#undef IMK_SLUG_INDEX
#define IMK_SLUG_INDEX IMK_SLUG_STRINGIFY(IMK_SLUG_ROOT_DIR/IMK_slug_index.h)
#include IMK_SLUG_INDEX

