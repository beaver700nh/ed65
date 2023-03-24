#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <curses.h>

#include "bar.hpp"
#include "text.hpp"

#include "main.hpp"

#include "highlight.hpp"

int main() {
  signal(SIGINT,  cleanup);
  signal(SIGHUP,  cleanup);
  signal(SIGTERM, cleanup);

  // Highlights highlights;
  // Highlighter::highlight(
  //   {
  //     "ALIAS = 3",
  //     "label:instr",
  //     "labeL: instr",
  //     "label:",
  //     "label: ",
  //     "  instr",
  //     "  instr op",
  //     "  instr op,x",
  //     "  instr #$5555",
  //     "  .dir asdf"
  //   },
  //   highlights
  // );

  // for (auto const &[row, hls] : highlights) {
  //   std::cout << row << ": ==============\n";
  //   for (auto const &hl : hls) {
  //     printf("{%d %d %d %d}\n", hl.start, hl.num, hl.color, hl.attrs);
  //   }
  // }

  // return 0;

  int rows, cols;
  startup(&rows, &cols);

  int main_width = cols * 0.75;

  WidgetFocus focus = WidgetFocus::TEXT_EDITOR;

  Text text {rows - 8, main_width - 1, 0, 0, focus};

  Bar bar {1, main_width - 3, rows - 10, 1, focus, text};

  WINDOW *docs = subwin(stdscr, rows - 8, cols - main_width, 0, main_width);
  box(docs, 0, 0);

  WINDOW *info = subwin(stdscr, 8, cols, rows - 8, 0);
  box(info, 0, 0);

  refresh();

  while (true) {
    text.draw();
    bar.draw();

    text.refresh();
    bar.refresh();

    text.draw_cursor();
    bar.draw_cursor();

    doupdate();

    int keystroke = getch();

    if (keystroke == ERR) {
      continue;
    }
    else if (keystroke == KEY_F(8)) {
      break;
    }

    bar.status_clear();

    text.tick(keystroke) &&
    bar.tick(keystroke);

    text.highlight();
  }

  cleanup(0);
}

void startup(int *rows, int *cols) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);

  if (has_colors()) {
    start_color();
    use_default_colors();

    // Assumes COLOR_XXX are implemented to be 0-7
    for (unsigned int color = 1; color < 8; ++color) {
      init_pair(color, color, -1);
    }
  }

  getmaxyx(stdscr, *rows, *cols);
}

void cleanup(int signal) {
  nocbreak();
  echo();
  endwin();

  exit(signal);
}

