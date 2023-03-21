#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <unordered_map>

#include <curses.h>

#include "common.hpp"

#include "text.hpp"

class Command {
public:
  Command() = delete;

  static void run(std::string command, Text &text);
};

#endif

