#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include <curses.h>

#include "common.hpp"

#include "text.hpp"

#define CALLBACK_DEF(name)      command_##name(Text &text, std::vector<std::string> args)
#define CALLBACK_TYPE           void (*)(Text &, std::vector<std::string>)
#define CALLBACK_REGISTER(name) {#name, command_##name}

class Command {
public:
  Command() = delete;

  static void run(std::string command, Text &text);

  static void CALLBACK_DEF(warp);

  static inline std::unordered_map<std::string, CALLBACK_TYPE> const callbacks {
    CALLBACK_REGISTER(warp),
  };
};

#endif
