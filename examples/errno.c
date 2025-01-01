#define USING_IMKLIB_ERROR_IMK_ERRNO
#include "imklib/error/IMK_errno.h"

#include <stdio.h>

int main(void) {
  SetError(41, "Sample error");
  if (GetErrorCode() == 30) {
    printf("You can't see me!");
  }
  PrintError("No!");
  ClearError();
  PrintError("Maybe?");
  return 0;
}

