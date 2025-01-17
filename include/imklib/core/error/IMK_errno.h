#ifndef IMKLIB_ERROR_IMK_ERRNO_H_
#define IMKLIB_ERROR_IMK_ERRNO_H_

void IMK_SetError(int errcode, char const *errmsg);
int IMK_GetErrorCode(void);
char const *IMK_GetErrorMessage(void);
void IMK_ClearError(void);
void IMK_PrintError(char const *str);

#ifdef USING_IMKLIB_ERROR_IMK_ERRNO
#define SetError IMK_SetError
#define GetErrorCode IMK_GetErrorCode
#define GetErrorMessage IMK_GetErrorMessage
#define ClearError IMK_ClearError
#define PrintError IMK_PrintError
#endif /* USING_IMKLIB_ERROR_IMK_ERRNO */

#endif /* !IMKLIB_ERROR_IMK_ERRNO_H_ */

