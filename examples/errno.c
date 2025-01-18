#include <stdio.h>

#define USING_NAMESPACE_IMK_ERRNO

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#include SLUG_IMK_HEADER_ERRNO

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
