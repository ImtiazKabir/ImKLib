#include <stdio.h>

#define SLUG_IMK_DIR_ROOT imklib
#include "imklib/IMK_slug_index_ref.h"

#include SLUG_IMK_HEADER_ANSI_STYLE

static void PrintDemo(char const *style, char const *text) {
  printf("%s%s%s\n", style, text, IMK_ANSI_RESET);
}

int main(void) {
  printf("Demonstrating ANSI Styles and Colors:\n\n");

  /* Text Styles */
  printf("Text Styles:\n");
  PrintDemo(IMK_ANSI_BOLD, "This is bold text");
  PrintDemo(IMK_ANSI_DIM, "This is dim text");
  PrintDemo(IMK_ANSI_ITALIC, "This is italic text");
  PrintDemo(IMK_ANSI_UNDERLINE, "This is underlined text");
  PrintDemo(IMK_ANSI_BLINK, "This is blinking text");
  PrintDemo(IMK_ANSI_INVERSE, "This is inverse text");
  PrintDemo(IMK_ANSI_HIDDEN, "This is hidden text");
  PrintDemo(IMK_ANSI_STRIKETHROUGH, "This is strikethrough text");

  /* Foreground Colors */
  printf("\nForeground Colors:\n");
  PrintDemo(IMK_ANSI_FG_BLACK, "Black text");
  PrintDemo(IMK_ANSI_FG_RED, "Red text");
  PrintDemo(IMK_ANSI_FG_GREEN, "Green text");
  PrintDemo(IMK_ANSI_FG_YELLOW, "Yellow text");
  PrintDemo(IMK_ANSI_FG_BLUE, "Blue text");
  PrintDemo(IMK_ANSI_FG_MAGENTA, "Magenta text");
  PrintDemo(IMK_ANSI_FG_CYAN, "Cyan text");
  PrintDemo(IMK_ANSI_FG_WHITE, "White text");
  PrintDemo(IMK_ANSI_FG_BRIGHT_BLACK, "Bright Black text");
  PrintDemo(IMK_ANSI_FG_BRIGHT_RED, "Bright Red text");
  PrintDemo(IMK_ANSI_FG_BRIGHT_GREEN, "Bright Green text");
  PrintDemo(IMK_ANSI_FG_BRIGHT_YELLOW, "Bright Yellow text");
  PrintDemo(IMK_ANSI_FG_BRIGHT_BLUE, "Bright Blue text");
  PrintDemo(IMK_ANSI_FG_BRIGHT_MAGENTA, "Bright Magenta text");
  PrintDemo(IMK_ANSI_FG_BRIGHT_CYAN, "Bright Cyan text");
  PrintDemo(IMK_ANSI_FG_BRIGHT_WHITE, "Bright White text");

  /* Background Colors */
  printf("\nBackground Colors:\n");
  PrintDemo(IMK_ANSI_BG_BLACK, "Black background");
  PrintDemo(IMK_ANSI_BG_RED, "Red background");
  PrintDemo(IMK_ANSI_BG_GREEN, "Green background");
  PrintDemo(IMK_ANSI_BG_YELLOW, "Yellow background");
  PrintDemo(IMK_ANSI_BG_BLUE, "Blue background");
  PrintDemo(IMK_ANSI_BG_MAGENTA, "Magenta background");
  PrintDemo(IMK_ANSI_BG_CYAN, "Cyan background");
  PrintDemo(IMK_ANSI_BG_WHITE, "White background");
  PrintDemo(IMK_ANSI_BG_BRIGHT_BLACK, "Bright Black background");
  PrintDemo(IMK_ANSI_BG_BRIGHT_RED, "Bright Red background");
  PrintDemo(IMK_ANSI_BG_BRIGHT_GREEN, "Bright Green background");
  PrintDemo(IMK_ANSI_BG_BRIGHT_YELLOW, "Bright Yellow background");
  PrintDemo(IMK_ANSI_BG_BRIGHT_BLUE, "Bright Blue background");
  PrintDemo(IMK_ANSI_BG_BRIGHT_MAGENTA, "Bright Magenta background");
  PrintDemo(IMK_ANSI_BG_BRIGHT_CYAN, "Bright Cyan background");
  PrintDemo(IMK_ANSI_BG_BRIGHT_WHITE, "Bright White background");

  return 0;
}
