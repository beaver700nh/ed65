#include <cctype>
#include <cstdlib>

#include <curses.h>

#include "common.cpp"

#include "text.hpp"

Text::Text(int rows, int cols, int row, int col) {
  frame = subwin(stdscr, rows, cols, row, col);
  box(frame, 0, 0);

  win = subwin(frame, rows - 2, cols - 2, 1, 1);
}

void Text::tick(int keystroke) {
  if (keystroke == KEY_F(1)) {
    --offset_y;
  }
  if (keystroke == KEY_F(2)) {
    ++offset_y;
  }
  if (keystroke == KEY_F(3)) {
    --offset_x;
  }
  if (keystroke == KEY_F(4)) {
    ++offset_x;
  }

  if (isprint(keystroke)) {
    add_letter(keystroke);
  }
}

void Text::draw() {
  werase(win);

  unsigned int const line_last = lines.size() - 1;
  unsigned int const line_first = constrain<int>(offset_y, 0, line_last);

  for (unsigned int line_no = line_first; line_no <= line_last; ++line_no) {
    int const row = line_no + offset_y;
    int const col = at_least<int>(offset_x, 0);

    if (row < 0) {
      continue; // skip if above top of screen
    }
    if (row >= getmaxy(win)) {
      break; // quit if bottom of screen is reached
    }
    if (col >= getmaxx(win)) {
      continue; // skip if to right of screen
    }

    draw_line(line_no, row, col);
  }

  draw_cursor();

  wnoutrefresh(win);
}

void Text::draw_line(unsigned int line_no, int row, int col) {
  auto const &line = lines.at(line_no);

  unsigned int const char_first = at_least<int>(-offset_x, 0);

  if (char_first >= line.size()) {
    return; // skip if to left of screen
  }

  unsigned int const segment = at_most<int>(getmaxx(win) - col, line.size() - char_first);

  mvwprintw(win, row, col, "%s", line.substr(char_first, segment).c_str());
}

void Text::draw_cursor() {
  int const row = cursor_y + offset_y;

  if (0 > row || row >= getmaxy(win)) {
    curs_set(false);
    return;
  }

  int const col = cursor_x + offset_x;

  if (0 > col || col >= getmaxx(win)) {
    curs_set(false);
    return;
  }

  wmove(win, row, col);
  curs_set(true);
}

void Text::add_letter(char letter) {
  if (lines.size() == 0) {
    lines.push_back("");
  }

  lines.at(cursor_y).insert(cursor_x++, 1, letter);
}
