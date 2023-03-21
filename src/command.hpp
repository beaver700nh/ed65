#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include <curses.h>

#include "common.hpp"

#include "text.hpp"

#define CALLBACK(name) command_##name(Text &text, std::vector<std::string> args)

class Command {
public:
  Command() = delete;

  static void run(std::string command, Text &text);

  static void CALLBACK(warp);

  std::unordered_map<std::string, void (*)(Text &, std::vector<std::string>)> callbacks;
};

#endif

