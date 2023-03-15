#ifndef COMMON_HPP
#define COMMON_HPP

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

#endif