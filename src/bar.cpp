#include <cstdarg>
#include <string>

#include <curses.h>

#include "common.hpp"

#include "command.hpp"
#include "text.hpp"

#include "bar.hpp"

Bar::Bar(int rows, int cols, int row, int col, WidgetFocus &focus, Text &text) : focus {focus}, text {text} {
  win = subwin(text.frame, rows, cols, row, col);
  wattrset(win, A_REVERSE);

  // -2 for command indicator and cursor; +1 for terminating null
  command_text = (char *) malloc((cols - 2 + 1) * (sizeof (char)));
  status_text = (char *) malloc((cols - 2 + 1) * (sizeof (char)));
  update_edit();
}

Bar::~Bar() {
  free((void *) command_text);
  free((void *) status_text);
}

bool Bar::tick(int keystroke) {
  if (focus != WidgetFocus::COMMAND_BAR) {
    return true;
  }

  if (keystroke == KEY_F(7)) {
    escape();
    return false;
  }

  if (keystroke == KEY_BACKSPACE || keystroke == '\x7f' || keystroke == '\b') {
    backspace();
  }
  else if (keystroke == KEY_ENTER || keystroke == '\n' || keystroke == '\r') {
    Command::run(command, text, *this);
    escape();
  }
  else if (isprint(keystroke)) {
    add_letter(keystroke);
  }

  return false;
}

void Bar::add_letter(char letter) {
  command.push_back(letter);
}

void Bar::backspace() {
  if (command.size() > 0) {
    command.pop_back();
  }
}

void Bar::escape() {
  focus = WidgetFocus::TEXT_EDITOR;
  command.clear();
}

void Bar::status_set(char const *format, ...) {
  va_list args;
  va_start(args, format);

  vsnprintf(status_text, getmaxx(win) + 1, format, args);

  va_end(args);
}

void Bar::status_clear() {
  *status_text = '\0';
}

void Bar::update() {
  if (focus == WidgetFocus::TEXT_EDITOR) {
    update_edit();
  }
  else if (focus == WidgetFocus::COMMAND_BAR) {
    update_command();
  }
}

void Bar::update_edit() {
  int const width = getmaxx(win);

  if (
    snprintf(
      command_text, width + 1, "%u~%u %d~%d %s",
      text.cursor_y, text.cursor_x,
      text.offset_y, text.offset_x,
      status_text
    ) > width
  ) {
    command_text[width - 1] = '~';
  }
}

void Bar::update_command() {
  // -2 for command indicator and cursor
  unsigned int space = at_least<int>(getmaxx(win) - 2, 0);

  if (command.size() <= space) {
    snprintf(command_text, getmaxx(win) + 1, ":%s", command.c_str());
  }
  else {
    // +1 for extra column taken by cutoff marker
    unsigned int index = at_least<int>(command.size() - space + 1, 0);
    std::string shortened = command.substr(index);

    snprintf(command_text, getmaxx(win) + 1, ":<%s", shortened.c_str());
  }
}

void Bar::draw() {
  update();

  wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); // easy way to fill with spaces
  mvwaddstr(win, 0, 0, command_text);
}

void Bar::draw_cursor() {
  if (focus != WidgetFocus::COMMAND_BAR) {
    return;
  }

  wmove(win, 0, at_most<int>(command.size() + 1, getmaxx(win))); // +1 for cursor
  curs_set(true);
  refresh();
}

void Bar::refresh() {
  wnoutrefresh(win);
}

