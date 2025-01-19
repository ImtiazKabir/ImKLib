#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#define USING_NAMESPACE_IMK_PRINTF
#include SLUG_IMK_HEADER_PRINTF

int main(void) {
  char buffer[100];
  SPrintF(buffer, "%d + %d = %d", 4, 5, 9);
  PrintF("%s\n", buffer);
  return 0;
}

