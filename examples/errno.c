#include <stdio.h>

#define USING_IMKLIB_ERROR_IMK_ERRNO

#define IMK_SLUG_EXTERN_ROOT_DIR imklib
#include "imklib/IMK_slug_index_ref.h"

#include IMK_SLUG_ERRNO

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
