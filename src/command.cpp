#include <cstdio>
#include <stdexcept>
#include <string>
#include <vector>

#include <curses.h>

#include "common.hpp"

#include "bar.hpp"
#include "text.hpp"

#include "command.hpp"

void Command::run(std::string command, Text &text, Bar &bar) {
  std::vector<std::string> arguments = wordify(command);

  if (arguments.size() == 0) {
    return;
  }

  std::string name = arguments.at(0);
  auto callback = callbacks.find(name);

  if (callback == callbacks.end()) {
    bar.status_set("Unrecognized command: '%s'", name.c_str());
    return;
  }

  unsigned int signature = callback->second.arguments;

  if (arguments.size() <= signature) {
    bar.status_set("Command '%s' requires >= %d arguments", name.c_str(), signature);
    return;
  }

  try {
    (*callback->second.function)(text, bar, arguments);
  }
  catch (std::exception const &e) {
    bar.status_set("Command '%s' had error: %s", name.c_str(), e.what());
  }
}

void Command::CALLBACK_DEF(warp) {
  (void) bar;

  int const row = std::stoi(args.at(1));
  int const col = std::stoi(args.at(2));

  int const cursor_y = constrain<int>(row, 0, text.lines.size() - 1);
  int const cursor_x = constrain<int>(col, 0, text.lines.at(cursor_y).size());

  text.cursor_y = cursor_y;
  text.cursor_x = cursor_x;

  int const offset_y = getmaxy(text.win) / 2 - cursor_y;
  int const offset_x = getmaxx(text.win) / 2 - cursor_x;

  text.offset_y = offset_y;
  text.offset_x = at_most<int>(offset_x, 0); // text should never be right-shifted past 0
}

