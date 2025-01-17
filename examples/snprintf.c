#include <stdio.h>
#include <stdlib.h>

#define USING_NAMESPACE_IMK_PRINTF_H_

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_slug_index_ref.h"

#include SLUG_IMK_HEADER_PRINTF

int main(void) {
  size_t n = (size_t)SNPrintF(NULL, 0, "%d IMKLib %f", 2005041, 3.141596);
  char *buf = malloc(n + 1);
  SNPrintF(buf, n + 1, "%d IMKLib %f", 2005041, 3.141596);
  puts(buf);
  free(buf);
  return 0;
}
