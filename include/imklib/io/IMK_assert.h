#ifndef IMKLIB_IO_IMK_ASSERT_H_
#define IMKLIB_IO_IMK_ASSERT_H_

typedef enum {
  IMK_PANIC_NONE,
  IMK_PANIC_BOX,
  IMK_PANIC_ALERT,
  IMK_PANIC_CAT
} IMK_PanicStyle;

void IMK_Panic(IMK_PanicStyle style, char const *msg);

#define IMK_ASSERT(cond)                                   \
  if (!(cond)) {                                           \
    IMK_Panic(IMK_PANIC_BOX, "Assertion error: " #cond);   \
  }

#define IMK_ASSERT_MSG(cond, msg)                      \
  if (!(cond)) {                                       \
    IMK_Panic(IMK_PANIC_BOX, msg);                     \
  }

#ifdef USING_IMKLIB_IO_IMK_ASSERT
#define PANIC_NONE IMK_PANIC_NONE
#define PANIC_BOX IMK_PANIC_BOX
#define PANIC_ALERT IMK_PANIC_ALERT
#define PANIC_CAT IMK_PANIC_CAT
typedef IMK_PanicStyle PanicStyle;
#define ASSERT IMK_ASSERT
#define ASSERT_MSG IMK_ASSERT_MSG
#endif /* USING_IMKLIB_IO_IMK_ASSERT */

#endif /* !IMKLIB_IO_IMK_ASSERT_H_ */

