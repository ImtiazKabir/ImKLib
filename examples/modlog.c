#define USING_IMKLIB_LOGGING_IMK_ANSI_STYLE
#define USING_IMKLIB_LOGGING_IMK_MODLOG

#define IMK_SLUG_EXTERN_ROOT_DIR imklib
#include "imklib/IMK_slug_index_ref.h"

#include IMK_SLUG_ANSI_STYLE
#include IMK_SLUG_MODLOG
#include IMK_SLUG_INTS

enum { YESS, HAHA, OHNO };

LogModule mylogger = {U32(-1),
                      {{YESS, "[YES]", ANSI_BG_WHITE ANSI_FG_BLACK,
                        ANSI_BG_DEFAULT ANSI_FG_DEFAULT},
                       {HAHA, "[HAHA]", ANSI_BG_DEFAULT ANSI_FG_YELLOW,
                        ANSI_BG_DEFAULT ANSI_FG_DEFAULT},
                       {OHNO, "[OHNO]", ANSI_BG_DEFAULT ANSI_FG_RED,
                        ANSI_BG_DEFAULT ANSI_FG_DEFAULT}}};

int main(void) {
  mylogger.mask &= ~(1u << YESS);

  ModLog(&mylogger, YESS, "Yess world\n");
  ModLog(&mylogger, HAHA, "Haha world %d\n", 2);
  ModLog(&mylogger, OHNO, "Ohno world\n");

  return 0;
}
