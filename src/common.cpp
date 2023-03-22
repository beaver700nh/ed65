#include <iterator>
#include <numeric>
#include <sstream>

#include "common.hpp"

std::vector<std::string> wordify(std::string str) {
  std::stringstream ss {str};

  std::istream_iterator<std::string> begin {ss};
  std::istream_iterator<std::string> end;

  std::vector<std::string> strs {begin, end};

  return strs;
}

std::string join(std::vector<std::string> list, std::string delimiter) {
  return std::accumulate(
    std::next(list.begin()), list.end(), list.at(0),
    [delimiter](std::string a, std::string b) {
      return a + delimiter + b;
    }
  );
}
