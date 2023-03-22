#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include <curses.h>

#include "common.hpp"

struct Highlight {
  int start;
  int num;
  int color;
};

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

  // line number : Highlight[]
  std::unordered_map<unsigned int, std::vector<Highlight>> highlights {
    {0, {{0, 3, 1}, {5, 1, 2}}},
    {2, {{1, 9, 1}, {2, 3, 2}}},
  };

  std::string filename {""};
};

#endif
