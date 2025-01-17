/* clang-format off */
#include "../IMK_slug_root_ref.h"

#undef IMK_SLUG_ROOT_DIR
#if(IMK_SLUG_DIR_LEVEL==0)
#undef IMK_SLUG_DIR_LEVEL
#define IMK_SLUG_DIR_LEVEL 1
#define IMK_SLUG_ROOT_DIR ..
#elif(IMK_SLUG_DIR_LEVEL==1)
#undef IMK_SLUG_DIR_LEVEL
#define IMK_SLUG_DIR_LEVEL 2
#define IMK_SLUG_ROOT_DIR ../..
#elif(IMK_SLUG_DIR_LEVEL==2)
#undef IMK_SLUG_DIR_LEVEL
#define IMK_SLUG_DIR_LEVEL 3
#define IMK_SLUG_ROOT_DIR ../../..
#elif(IMK_SLUG_DIR_LEVEL==3)
#undef IMK_SLUG_DIR_LEVEL
#define IMK_SLUG_DIR_LEVEL 4
#define IMK_SLUG_ROOT_DIR ../../../..
#elif(IMK_SLUG_DIR_LEVEL==4)
#undef IMK_SLUG_DIR_LEVEL
#define IMK_SLUG_DIR_LEVEL 5
#define IMK_SLUG_ROOT_DIR ../../../../..
#elif(IMK_SLUG_DIR_LEVEL==5)
#undef IMK_SLUG_DIR_LEVEL
#define IMK_SLUG_DIR_LEVEL 6
#define IMK_SLUG_ROOT_DIR ../../../../../..
#elif(IMK_SLUG_DIR_LEVEL==6)
#undef IMK_SLUG_DIR_LEVEL
#define IMK_SLUG_DIR_LEVEL 7
#define IMK_SLUG_ROOT_DIR ../../../../../../..
#elif(IMK_SLUG_DIR_LEVEL==7)
#undef IMK_SLUG_DIR_LEVEL
#define IMK_SLUG_DIR_LEVEL 8
#define IMK_SLUG_ROOT_DIR ../../../../../../../..
#elif(IMK_SLUG_DIR_LEVEL==8)
#error Too many level of nesting
#endif /* IMK_SLUG_DIR_LEVEL==0 */

