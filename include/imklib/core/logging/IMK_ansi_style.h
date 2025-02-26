#ifndef IMK_ANSI_STYLE_H_YNTTLMJZ81FNPCDW
#define IMK_ANSI_STYLE_H_YNTTLMJZ81FNPCDW

#define IMK_ANSI_RESET "\033[0m"

/* Text styles */
#define IMK_ANSI_BOLD "\033[1m"
#define IMK_ANSI_DIM "\033[2m"
#define IMK_ANSI_ITALIC "\033[3m"
#define IMK_ANSI_UNDERLINE "\033[4m"
#define IMK_ANSI_BLINK "\033[5m"
#define IMK_ANSI_INVERSE "\033[7m"
#define IMK_ANSI_HIDDEN "\033[8m"
#define IMK_ANSI_STRIKETHROUGH "\033[9m"

/* Foreground colors */
#define IMK_ANSI_FG_DEFAULT "\033[39m"
#define IMK_ANSI_FG_BLACK "\033[30m"
#define IMK_ANSI_FG_RED "\033[31m"
#define IMK_ANSI_FG_GREEN "\033[32m"
#define IMK_ANSI_FG_YELLOW "\033[33m"
#define IMK_ANSI_FG_BLUE "\033[34m"
#define IMK_ANSI_FG_MAGENTA "\033[35m"
#define IMK_ANSI_FG_CYAN "\033[36m"
#define IMK_ANSI_FG_WHITE "\033[37m"
#define IMK_ANSI_FG_BRIGHT_BLACK "\033[90m"
#define IMK_ANSI_FG_BRIGHT_RED "\033[91m"
#define IMK_ANSI_FG_BRIGHT_GREEN "\033[92m"
#define IMK_ANSI_FG_BRIGHT_YELLOW "\033[93m"
#define IMK_ANSI_FG_BRIGHT_BLUE "\033[94m"
#define IMK_ANSI_FG_BRIGHT_MAGENTA "\033[95m"
#define IMK_ANSI_FG_BRIGHT_CYAN "\033[96m"
#define IMK_ANSI_FG_BRIGHT_WHITE "\033[97m"

/* Background colors */
#define IMK_ANSI_BG_DEFAULT "\033[49m"
#define IMK_ANSI_BG_BLACK "\033[40m"
#define IMK_ANSI_BG_RED "\033[41m"
#define IMK_ANSI_BG_GREEN "\033[42m"
#define IMK_ANSI_BG_YELLOW "\033[43m"
#define IMK_ANSI_BG_BLUE "\033[44m"
#define IMK_ANSI_BG_MAGENTA "\033[45m"
#define IMK_ANSI_BG_CYAN "\033[46m"
#define IMK_ANSI_BG_WHITE "\033[47m"
#define IMK_ANSI_BG_BRIGHT_BLACK "\033[100m"
#define IMK_ANSI_BG_BRIGHT_RED "\033[101m"
#define IMK_ANSI_BG_BRIGHT_GREEN "\033[102m"
#define IMK_ANSI_BG_BRIGHT_YELLOW "\033[103m"
#define IMK_ANSI_BG_BRIGHT_BLUE "\033[104m"
#define IMK_ANSI_BG_BRIGHT_MAGENTA "\033[105m"
#define IMK_ANSI_BG_BRIGHT_CYAN "\033[106m"
#define IMK_ANSI_BG_BRIGHT_WHITE "\033[107m"

#ifdef USING_NAMESPACE_IMK_ANSI_STYLE
#include "IMK_index_ref.slug"
#include SLUG_IMK_ATTACH_ANSI_STYLE
#endif /* USING_NAMESPACE_IMK_ANSI_STYLE */

#endif /* !IMK_ANSI_STYLE_H_YNTTLMJZ81FNPCDW */
