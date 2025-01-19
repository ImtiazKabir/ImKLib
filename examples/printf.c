#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_index_ref.slug"

#define USING_NAMESPACE_IMK_PRINTF
#include SLUG_IMK_HEADER_PRINTF

int main(void) {
  PrintF("%obj\n", 2005041);
  return 0;
}

