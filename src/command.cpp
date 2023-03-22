#include <stdexcept>
#include <string>
#include <vector>

#include <curses.h>

#include "common.hpp"

#include "text.hpp"

#include "command.hpp"

void Command::run(std::string command, Text &text) {
  std::vector<std::string> arguments = wordify(command);

  if (arguments.size() == 0) {
    return;
  }

  std::string instruction = arguments.at(0);

  try {
    callbacks.at(instruction)(text, arguments);
  }
  catch (std::out_of_range &e) {
    text.lines.push_back("HELLO!");
  }
}

void Command::CALLBACK_DEF(warp) {
  if (args.size() <= 2) {
    text.lines.push_back("Hmmm.");
    return;
  }

  // implementation TODO
}

