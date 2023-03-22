#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include <curses.h>

#include "common.hpp"

#include "bar.hpp"
#include "text.hpp"

#define CALLBACK_DEF(name) command_##name(Text &text, Bar &bar, std::vector<std::string> args)
#define CALLBACK_REGISTER(name, args) {#name, {command_##name, args}}

class Command {
public:
  Command() = delete;

  static void run(std::string command, Text &text, Bar &bar);

  static void CALLBACK_DEF(warp);
  static void CALLBACK_DEF(save);
  static void CALLBACK_DEF(load);

private:
  using CallbackType = void (*)(Text &, Bar &, std::vector<std::string>);
  using CallbackInfo = struct { CallbackType function; unsigned int arguments; };

  static inline std::unordered_map<std::string, CallbackInfo> const callbacks {
    CALLBACK_REGISTER(warp, 2),
    CALLBACK_REGISTER(save, 0),
    CALLBACK_REGISTER(load, 1),
  };
};

#endif
