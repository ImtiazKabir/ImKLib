/* clang-format off */
#ifdef SLUG_IMK_DIR_ROOT
#define SLUG_IMK_DIR_INTERN_ROOT SLUG_IMK_DIR_ROOT
#else
#include "IMK_slug_root_ref.h"
#endif

#ifndef SLUG_STRINGIFY
#define SLUG_XSTRINGIFY(x) #x
#define SLUG_STRINGIFY(x) SLUG_XSTRINGIFY(x)
#endif /* SLUG_STRINGIFY */

#undef SLUG_IMK_HEADER_INDEX
#define SLUG_IMK_HEADER_INDEX SLUG_STRINGIFY(SLUG_IMK_DIR_INTERN_ROOT/IMK_slug_index.h)
#include SLUG_IMK_HEADER_INDEX

