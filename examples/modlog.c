#define USING_IMKLIB_LOGGING_IMK_ANSI_STYLE
#include "imklib/logging/IMK_ansi_style.h"
#define USING_IMKLIB_LOGGING_IMK_MODLOG
#include "imklib/logging/IMK_modlog.h"

#include "imklib/base/IMK_ints.h"

enum {
  YESS,
  HAHA,
  OHNO
};

LogModule mylogger = {
  U32(-1),
  {
    {YESS, "[YES]", ANSI_BG_WHITE, ANSI_FG_BLACK, ANSI_BG_DEFAULT, ANSI_FG_DEFAULT},
    {HAHA, "[HAHA]", ANSI_BG_DEFAULT, ANSI_FG_YELLOW, ANSI_BG_DEFAULT, ANSI_FG_DEFAULT},
    {OHNO, "[OHNO]", ANSI_BG_DEFAULT, ANSI_FG_RED, ANSI_BG_DEFAULT, ANSI_FG_DEFAULT}
  }
};

int main(void) {
  mylogger.mask &= ~(1u << YESS);

  ModLog(&mylogger, YESS, "Yess world\n");
  ModLog(&mylogger, HAHA, "Haha world %d\n", 2);
  ModLog(&mylogger, OHNO, "Ohno world\n");


  return 0;
}



