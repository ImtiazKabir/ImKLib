#ifndef IMK_ASSERT_H_LYBOWAACF1AEFYSI
#define IMK_ASSERT_H_LYBOWAACF1AEFYSI

void IMK_Panic(char const *msg);
void IMK_PanicBox(char const *msg);

#define IMK_ASSERT(cond)                                                       \
  if (!(cond)) {                                                               \
    IMK_PanicBox("Assertion error: " #cond);                                   \
  }

#define IMK_ASSERT_MSG(cond, msg)                                              \
  if (!(cond)) {                                                               \
    IMK_PanicBox(msg);                                                         \
  }

#ifdef USING_NAMESPACE_IMK_ASSERT
#define Panic IMK_Panic
#define PanicBox IMK_PanicBox
#define ASSERT IMK_ASSERT
#define ASSERT_MSG IMK_ASSERT_MSG
#endif /* USING_NAMESPACE_IMK_ASSERT */

#endif /* !IMK_ASSERT_H_LYBOWAACF1AEFYSI */
