#include "imklib/core/ptr/IMK_Ptr.h"

void IMK_Ptr_AsOwned(IMK_Ptr *ptr, void *cptr) {
  ptr->cptr = cptr;
  ptr->flags = IMK_PTR_OWNED;
}

void IMK_Ptr_AsBorrowed(IMK_Ptr *ptr, void *cptr) {
  ptr->cptr = cptr;
  ptr->flags = IMK_PTR_BORROWED;
}


