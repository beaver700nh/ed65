#ifndef BAR_HPP
#define BAR_HPP

#include <cstdarg>
#include <string>

#include <curses.h>

#include "common.hpp"

#include "text.hpp"

class Bar {
public:
  Bar(int rows, int cols, int row, int col, WidgetFocus &focus, Text &text);
  ~Bar();

  bool tick(int keystroke);

  void add_letter(char letter);
  void backspace();

  void escape();

  void set_status(char const *format, ...);

  void update();
  void update_edit();
  void update_command();

  void draw();
  void draw_cursor();

  void refresh();

private:
  WidgetFocus &focus;

  Text &text;

  WINDOW *win;

  std::string command;
  char *command_text;
  char *status_text;
};

#endif

