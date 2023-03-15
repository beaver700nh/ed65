#include <csignal>
#include <cstdlib>
#include <iostream>

#include <curses.h>

#include "text.hpp"

#include "main.hpp"

int main() {
  signal(SIGINT, cleanup);

  int rows, cols;
  startup(&rows, &cols);

  int main_width = cols * 0.75;

  Text text {rows - 8, main_width - 1, 0, 0};

  WINDOW *docs = subwin(stdscr, rows - 8, cols - main_width, 0, main_width);
  box(docs, 0, 0);

  WINDOW *info = subwin(stdscr, 8, cols, rows - 8, 0);
  box(info, 0, 0);

  refresh();

  while (true) {
    int keystroke = getch();

    if (keystroke == ERR) {
      continue;
    }
    else if (keystroke == KEY_F(8)) {
      break;
    }

    text.tick(keystroke);
    text.draw();

    doupdate();
  }

  cleanup(0);
}

void startup(int *rows, int *cols) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);

  getmaxyx(stdscr, *rows, *cols);
}

void cleanup(int signal) {
  nocbreak();
  echo();
  endwin();

  exit(signal);
}

