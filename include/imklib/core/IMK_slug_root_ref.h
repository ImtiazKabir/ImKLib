/* clang-format off */
#include "../IMK_slug_root_ref.h"

#undef SLUG_IMK_DIR_INTERN_ROOT
#if(SLUG_IMK_DIR_LEVEL==0)
#undef SLUG_IMK_DIR_LEVEL
#define SLUG_IMK_DIR_LEVEL 1
#define SLUG_IMK_DIR_INTERN_ROOT ..
#elif(SLUG_IMK_DIR_LEVEL==1)
#undef SLUG_IMK_DIR_LEVEL
#define SLUG_IMK_DIR_LEVEL 2
#define SLUG_IMK_DIR_INTERN_ROOT ../..
#elif(SLUG_IMK_DIR_LEVEL==2)
#undef SLUG_IMK_DIR_LEVEL
#define SLUG_IMK_DIR_LEVEL 3
#define SLUG_IMK_DIR_INTERN_ROOT ../../..
#elif(SLUG_IMK_DIR_LEVEL==3)
#undef SLUG_IMK_DIR_LEVEL
#define SLUG_IMK_DIR_LEVEL 4
#define SLUG_IMK_DIR_INTERN_ROOT ../../../..
#elif(SLUG_IMK_DIR_LEVEL==4)
#undef SLUG_IMK_DIR_LEVEL
#define SLUG_IMK_DIR_LEVEL 5
#define SLUG_IMK_DIR_INTERN_ROOT ../../../../..
#elif(SLUG_IMK_DIR_LEVEL==5)
#undef SLUG_IMK_DIR_LEVEL
#define SLUG_IMK_DIR_LEVEL 6
#define SLUG_IMK_DIR_INTERN_ROOT ../../../../../..
#elif(SLUG_IMK_DIR_LEVEL==6)
#undef SLUG_IMK_DIR_LEVEL
#define SLUG_IMK_DIR_LEVEL 7
#define SLUG_IMK_DIR_INTERN_ROOT ../../../../../../..
#elif(SLUG_IMK_DIR_LEVEL==7)
#undef SLUG_IMK_DIR_LEVEL
#define SLUG_IMK_DIR_LEVEL 8
#define SLUG_IMK_DIR_INTERN_ROOT ../../../../../../../..
#elif(SLUG_IMK_DIR_LEVEL==8)
#error Too many level of nesting
#endif /* SLUG_IMK_DIR_LEVEL==0 */

