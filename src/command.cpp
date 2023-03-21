#include <string>
#include <vector>

#include <curses.h>

#include "common.hpp"

#include "text.hpp"

#include "command.hpp"

void Command::run(std::string command, Text &text) {
  std::vector<std::string> arguments = wordify(command);

  command_warp(text, arguments);
}

void Command::CALLBACK(warp) {
  text.lines.insert(text.lines.end(), args.cbegin(), args.cend());
}

