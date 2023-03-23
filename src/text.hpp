#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include <curses.h>

#include "common.hpp"

#include "highlight.hpp"

class Text {
  friend class Bar;
  friend class Command;

public:
  Text(int rows, int cols, int row, int col, WidgetFocus &focus);
  ~Text();

  bool tick(int keystroke);

  void bindings_offset(int keystroke);
  void bindings_cursor(int keystroke);

  void cursor_home();
  void cursor_end();
  void cursor_page_up();
  void cursor_page_down();

  void add_letter(char letter);
  void add_line();
  void backspace();

  void highlight();

  void draw();
  void draw_line(unsigned int line_no, unsigned int row, unsigned int col);
  void draw_highlights(unsigned int line_no, unsigned int row, unsigned int col);
  void draw_cursor();

  void refresh();

private:
  WidgetFocus &focus;

  WINDOW *frame;
  WINDOW *win;

  int offset_x = 0;
  int offset_y = 0;

  unsigned int cursor_x = 0;
  unsigned int cursor_y = 0;

  std::vector<std::string> lines {""};

  Highlights highlights;

  std::string filename {""};
};

#endif
