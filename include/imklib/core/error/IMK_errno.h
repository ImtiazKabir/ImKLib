#ifndef IMK_ERRNO_H_0MRMCKJOSGDQQFAH
#define IMK_ERRNO_H_0MRMCKJOSGDQQFAH

void IMK_SetError(int errcode, char const *errmsg);
int IMK_GetErrorCode(void);
char const *IMK_GetErrorMessage(void);
void IMK_ClearError(void);
void IMK_PrintError(char const *str);

#ifdef USING_NAMESPACE_IMK_ERRNO
#define SetError IMK_SetError
#define GetErrorCode IMK_GetErrorCode
#define GetErrorMessage IMK_GetErrorMessage
#define ClearError IMK_ClearError
#define PrintError IMK_PrintError
#endif /* USING_NAMESPACE_IMK_ERRNO */

#endif /* !IMK_ERRNO_H_0MRMCKJOSGDQQFAH */
