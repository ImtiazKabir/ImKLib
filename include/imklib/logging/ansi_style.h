#ifndef IMKLIB_LOGGING_ANSI_STYLE_H_
#define IMKLIB_LOGGING_ANSI_STYLE_H_

#define IMK_ANSI_RESET          "\033[0m"

/* Text styles */
#define IMK_ANSI_BOLD           "\033[1m"
#define IMK_ANSI_DIM            "\033[2m"
#define IMK_ANSI_ITALIC         "\033[3m"
#define IMK_ANSI_UNDERLINE      "\033[4m"
#define IMK_ANSI_BLINK          "\033[5m"
#define IMK_ANSI_INVERSE        "\033[7m"
#define IMK_ANSI_HIDDEN         "\033[8m"
#define IMK_ANSI_STRIKETHROUGH  "\033[9m"

/* Foreground colors */
#define IMK_ANSI_FG_DEFAULT     "\033[39m"
#define IMK_ANSI_FG_BLACK       "\033[30m"
#define IMK_ANSI_FG_RED         "\033[31m"
#define IMK_ANSI_FG_GREEN       "\033[32m"
#define IMK_ANSI_FG_YELLOW      "\033[33m"
#define IMK_ANSI_FG_BLUE        "\033[34m"
#define IMK_ANSI_FG_MAGENTA     "\033[35m"
#define IMK_ANSI_FG_CYAN        "\033[36m"
#define IMK_ANSI_FG_WHITE       "\033[37m"
#define IMK_ANSI_FG_BRIGHT_BLACK "\033[90m"
#define IMK_ANSI_FG_BRIGHT_RED  "\033[91m"
#define IMK_ANSI_FG_BRIGHT_GREEN "\033[92m"
#define IMK_ANSI_FG_BRIGHT_YELLOW "\033[93m"
#define IMK_ANSI_FG_BRIGHT_BLUE "\033[94m"
#define IMK_ANSI_FG_BRIGHT_MAGENTA "\033[95m"
#define IMK_ANSI_FG_BRIGHT_CYAN "\033[96m"
#define IMK_ANSI_FG_BRIGHT_WHITE "\033[97m"

/* Background colors */
#define IMK_ANSI_BG_DEFAULT     "\033[49m"
#define IMK_ANSI_BG_BLACK       "\033[40m"
#define IMK_ANSI_BG_RED         "\033[41m"
#define IMK_ANSI_BG_GREEN       "\033[42m"
#define IMK_ANSI_BG_YELLOW      "\033[43m"
#define IMK_ANSI_BG_BLUE        "\033[44m"
#define IMK_ANSI_BG_MAGENTA     "\033[45m"
#define IMK_ANSI_BG_CYAN        "\033[46m"
#define IMK_ANSI_BG_WHITE       "\033[47m"
#define IMK_ANSI_BG_BRIGHT_BLACK "\033[100m"
#define IMK_ANSI_BG_BRIGHT_RED  "\033[101m"
#define IMK_ANSI_BG_BRIGHT_GREEN "\033[102m"
#define IMK_ANSI_BG_BRIGHT_YELLOW "\033[103m"
#define IMK_ANSI_BG_BRIGHT_BLUE "\033[104m"
#define IMK_ANSI_BG_BRIGHT_MAGENTA "\033[105m"
#define IMK_ANSI_BG_BRIGHT_CYAN "\033[106m"
#define IMK_ANSI_BG_BRIGHT_WHITE "\033[107m"

#ifdef USING_IMKLIB_LOGGING_ANSI_STYLE
#define IMK_ANSI_RESET      ANSI_RESET

/* Text styles */
#define ANSI_BOLD           IMK_ANSI_BOLD
#define ANSI_DIM            IMK_ANSI_DIM          
#define ANSI_ITALIC         IMK_ANSI_ITALIC       
#define ANSI_UNDERLINE      IMK_ANSI_UNDERLINE    
#define ANSI_BLINK          IMK_ANSI_BLINK        
#define ANSI_INVERSE        IMK_ANSI_INVERSE      
#define ANSI_HIDDEN         IMK_ANSI_HIDDEN       
#define ANSI_STRIKETHROUGH  IMK_ANSI_STRIKETHROUGH

/* Foreground colors */
#define ANSI_FG_DEFAULT          IMK_ANSI_FG_DEFAULT       
#define ANSI_FG_BLACK            IMK_ANSI_FG_BLACK         
#define ANSI_FG_RED              IMK_ANSI_FG_RED           
#define ANSI_FG_GREEN            IMK_ANSI_FG_GREEN         
#define ANSI_FG_YELLOW           IMK_ANSI_FG_YELLOW        
#define ANSI_FG_BLUE             IMK_ANSI_FG_BLUE          
#define ANSI_FG_MAGENTA          IMK_ANSI_FG_MAGENTA       
#define ANSI_FG_CYAN             IMK_ANSI_FG_CYAN          
#define ANSI_FG_WHITE            IMK_ANSI_FG_WHITE         
#define ANSI_FG_BRIGHT_BLACK     IMK_ANSI_FG_BRIGHT_BLACK  
#define ANSI_FG_BRIGHT_RED       IMK_ANSI_FG_BRIGHT_RED    
#define ANSI_FG_BRIGHT_GREEN     IMK_ANSI_FG_BRIGHT_GREEN  
#define ANSI_FG_BRIGHT_YELLOW    IMK_ANSI_FG_BRIGHT_YELLOW 
#define ANSI_FG_BRIGHT_BLUE      IMK_ANSI_FG_BRIGHT_BLUE   
#define ANSI_FG_BRIGHT_MAGENTA   IMK_ANSI_FG_BRIGHT_MAGENTA
#define ANSI_FG_BRIGHT_CYAN      IMK_ANSI_FG_BRIGHT_CYAN   
#define ANSI_FG_BRIGHT_WHITE     IMK_ANSI_FG_BRIGHT_WHITE  

/* Background colors */
#define ANSI_BG_DEFAULT              IMK_ANSI_BG_DEFAULT       
#define ANSI_BG_BLACK                IMK_ANSI_BG_BLACK         
#define ANSI_BG_RED                  IMK_ANSI_BG_RED           
#define ANSI_BG_GREEN                IMK_ANSI_BG_GREEN         
#define ANSI_BG_YELLOW               IMK_ANSI_BG_YELLOW        
#define ANSI_BG_BLUE                 IMK_ANSI_BG_BLUE          
#define ANSI_BG_MAGENTA              IMK_ANSI_BG_MAGENTA       
#define ANSI_BG_CYAN                 IMK_ANSI_BG_CYAN          
#define ANSI_BG_WHITE                IMK_ANSI_BG_WHITE         
#define ANSI_BG_BRIGHT_BLACK         IMK_ANSI_BG_BRIGHT_BLACK  
#define ANSI_BG_BRIGHT_RED           IMK_ANSI_BG_BRIGHT_RED    
#define ANSI_BG_BRIGHT_GREEN         IMK_ANSI_BG_BRIGHT_GREEN  
#define ANSI_BG_BRIGHT_YELLOW        IMK_ANSI_BG_BRIGHT_YELLOW 
#define ANSI_BG_BRIGHT_BLUE          IMK_ANSI_BG_BRIGHT_BLUE   
#define ANSI_BG_BRIGHT_MAGENTA       IMK_ANSI_BG_BRIGHT_MAGENTA
#define ANSI_BG_BRIGHT_CYAN          IMK_ANSI_BG_BRIGHT_CYAN   
#define ANSI_BG_BRIGHT_WHITE         IMK_ANSI_BG_BRIGHT_WHITE  

#endif /* USING_IMKLIB_LOGGING_ANSI_STYLE */

#endif /* !IMKLIB_LOGGING_ANSI_STYLE_H_ */

