#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

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

  unsigned int signature = callback->second.min_arguments;

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
  int const col = (args.size() > 2 ? std::stoi(args.at(2)) : 0);

  int const cursor_y = constrain<int>(row, 0, text.lines.size() - 1);
  int const cursor_x = constrain<int>(col, 0, text.lines.at(cursor_y).size());

  text.cursor_y = cursor_y;
  text.cursor_x = cursor_x;

  int const offset_y = getmaxy(text.win) / 2 - cursor_y;
  int const offset_x = getmaxx(text.win) / 2 - cursor_x;

  text.offset_y = offset_y;
  text.offset_x = at_most<int>(offset_x, 0); // text should never be right-shifted past 0
}

void Command::CALLBACK_DEF(save) {
  (void) bar;

  void _save_file(std::string filename, std::vector<std::string> lines);

  if (args.size() > 1) {
    text.filename = args.at(1);
  }

  if (text.filename == "") {
    throw std::runtime_error("No filename is given or cached");
  }

  _save_file(text.filename, text.lines);
}

void _save_file(std::string filename, std::vector<std::string> lines) {
  (std::ofstream {filename.c_str()} << join(lines, "\n")).close();
}

void Command::CALLBACK_DEF(load) {
  (void) bar;

  void _load_file(std::string filename, std::vector<std::string> &lines);

  _load_file(args.at(1), text.lines);
  text.cursor_x = text.cursor_y = text.offset_x = text.offset_y = 0;
}

void _load_file(std::string filename, std::vector<std::string> &lines) {
  std::ifstream file {filename.c_str()};

  if (!file) {
    throw std::runtime_error("Failed to open file");
  }

  std::string line;

  lines.clear();

  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  file.close();

  // Text editor cannot be empty
  if (lines.size() == 0) {
    lines.push_back("");
  }
}
