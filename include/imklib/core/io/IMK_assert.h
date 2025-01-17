#ifndef IMKLIB_IO_IMK_ASSERT_H_
#define IMKLIB_IO_IMK_ASSERT_H_

void IMK_Panic(char const *msg);
void IMK_PanicBox(char const *msg);

#define IMK_ASSERT(cond)                                   \
  if (!(cond)) {                                           \
    IMK_PanicBox("Assertion error: " #cond);               \
  }

#define IMK_ASSERT_MSG(cond, msg)                      \
  if (!(cond)) {                                       \
    IMK_PanicBox(msg);                                 \
  }

#ifdef USING_IMKLIB_IO_IMK_ASSERT
#define Panic IMK_Panic
#define PanicBox IMK_PanicBox
#define ASSERT IMK_ASSERT
#define ASSERT_MSG IMK_ASSERT_MSG
#endif /* USING_IMKLIB_IO_IMK_ASSERT */

#endif /* !IMKLIB_IO_IMK_ASSERT_H_ */

