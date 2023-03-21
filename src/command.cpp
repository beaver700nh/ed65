#include <string>

#include <curses.h>

#include "common.hpp"

#include "text.hpp"

#include "command.hpp"

void Command::run(std::string command, Text &text) {
  text.lines.push_back(command);
}

