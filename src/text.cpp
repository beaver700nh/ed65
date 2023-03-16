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
  bindings_offset(keystroke);
  bindings_cursor(keystroke);

  if (keystroke == KEY_BACKSPACE || keystroke == '\x7f' || keystroke == '\b') {
    backspace();
  }
  else if (keystroke == '\n' || keystroke == '\r') {
    add_line();
  }
  else if (keystroke == KEY_HOME) {
    cursor_home();
  }
  else if (keystroke == KEY_END) {
    cursor_end();
  }
  else if (keystroke == KEY_PPAGE) {
    cursor_page_up();
  }
  else if (keystroke == KEY_NPAGE) {
    cursor_page_down();
  }
  else if (isprint(keystroke)) {
    add_letter(keystroke);
  }
}

void Text::bindings_offset(int keystroke) {
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
}

void Text::bindings_cursor(int keystroke) {
  if (keystroke == KEY_UP && cursor_y > 0) {
    --cursor_y;
  }
  if (keystroke == KEY_DOWN && cursor_y + 1 < lines.size()) {
    ++cursor_y;
  }
  if (keystroke == KEY_LEFT && cursor_x > 0) {
    --cursor_x;
  }
  if (keystroke == KEY_RIGHT && cursor_x < lines.at(cursor_y).size()) {
    ++cursor_x;
  }
}

void Text::cursor_home() {
  cursor_x = 0;
}

void Text::cursor_end() {
  cursor_x = lines.at(cursor_y).size();
}

void Text::cursor_page_up() {
  if (cursor_y == 0) {
    cursor_x = 0;
  }

  cursor_y -= at_most<unsigned int>(getmaxy(win) - 1, cursor_y);
}

void Text::cursor_page_down() {
  auto max = lines.size() - 1;

  if (cursor_y == max) {
    cursor_end();
  }

  cursor_y += at_most<unsigned int>(getmaxy(win) - 1, lines.size() - 1 - cursor_y);
}

void Text::add_letter(char letter) {
  auto &line = lines.at(cursor_y);

  if (cursor_x > line.length()) {
    cursor_end();
  }

  line.insert(cursor_x++, 1, letter);
}

void Text::add_line() {
  auto const &line = lines.at(cursor_y);

  if (cursor_x > line.length()) {
    cursor_end();
  }

  std::string lhs = line.substr(0, cursor_x);
  std::string rhs = line.substr(cursor_x);

  lines.at(cursor_y++) = lhs;
  lines.insert(lines.cbegin() + cursor_y, rhs);

  cursor_x = 0;
}

void Text::backspace() {
  auto &line = lines.at(cursor_y);

  if (cursor_x == 0) {
    if (cursor_y == 0) {
      return; // can't delete past the beginning
    }

    lines.at(cursor_y - 1).append(line);
    lines.erase(lines.begin() + cursor_y--);

    cursor_x = lines.at(cursor_y).size();
  }
  else {
    line.erase(--cursor_x, 1);
  }
}

void Text::draw() {
  werase(win);

  unsigned int const line_last = lines.size() - 1;
  unsigned int const line_first = at_least<int>(-offset_y, 0);

  for (unsigned int line_no = line_first; line_no <= line_last; ++line_no) {
    unsigned int const row = line_no + offset_y;
    unsigned int const col = at_least<int>(offset_x, 0);

    if (row >= static_cast<unsigned int>(getmaxy(win))) {
      break; // quit if bottom of screen is reached
    }
    if (col >= static_cast<unsigned int>(getmaxx(win))) {
      continue; // skip if to right of screen
    }

    draw_line(line_no, row, col);
  }

  draw_cursor();

  wnoutrefresh(win);
}

void Text::draw_line(unsigned int line_no, unsigned int row, unsigned int col) {
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

  wmove(win, row, at_most<int>(col, lines.at(cursor_y).size()));
  curs_set(true);
}

void Text::refresh() {
  wrefresh(win);
}

