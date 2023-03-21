#include <iterator>
#include <sstream>

#include "common.hpp"

std::vector<std::string> wordify(std::string str) {
  std::stringstream ss {str};

  std::istream_iterator<std::string> begin {ss};
  std::istream_iterator<std::string> end;

  std::vector<std::string> strs {begin, end};

  return strs;
}

