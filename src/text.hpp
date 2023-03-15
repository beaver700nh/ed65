#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>
#include <vector>

#include <curses.h>

struct Highlight {
  int color;
  int start;
  int end;
};

class Text {
public:
  Text(int rows, int cols, int row, int col);

  void tick(int keystroke);

  void add_letter(char letter);

  void draw();
  void draw_line(unsigned int line_no, int row, int col);
  void draw_cursor();

private:
  WINDOW *frame;
  WINDOW *win;

  int offset_x = 0;
  int offset_y = 0;

  int cursor_x = 0;
  int cursor_y = 0;

  std::vector<std::string> lines;
  std::vector<std::vector<Highlight>> highlights;
};

#endif
