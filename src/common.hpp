#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <vector>

enum class WidgetFocus {
  TEXT_EDITOR,
  COMMAND_BAR,
};

template<typename T>
T constrain(T value, T min, T max) {
  if (value < min) {
    return min;
  }
  else if (value > max) {
    return max;
  }
  else {
    return value;
  }
}

template<typename T>
T at_least(T value, T min) {
  if (value < min) {
    return min;
  }
  else {
    return value;
  }
}

template<typename T>
T at_most(T value, T max) {
  if (value > max) {
    return max;
  }
  else {
    return value;
  }
}

std::vector<std::string> wordify(std::string str);
std::string join(std::vector<std::string> list, std::string delimiter);

#endif
