//
// Created by zcy on 2024/12/10.
//

#include "../include/Unit.hpp"

#include <cstring>

template <typename T>
Unit<T>::Unit(const char *str) {
  memset(index, 0, sizeof(index));
  strcpy(index, str);
}

template <typename T>
Unit<T>::Unit(const char *str, T val) : value(val) {
  memset(index, 0, sizeof(index));
  strcpy(index, str);
}

template <typename T>
bool Unit<T>::operator<(const Unit &other) const {
  int tmp = strcmp(index, other.index);
  if (tmp != 0) {
    return tmp < 0;
  }
  return value < other.value;
}

template <typename T>
bool Unit<T>::operator>(const Unit &other) const {
  return other.operator<(this);
}

template <typename T>
bool Unit<T>::operator<=(const Unit &other) const {
  return operator>(other) ^ 1;
}

template <typename T>
bool Unit<T>::operator>=(const Unit &other) const {
  return operator<(other) ^ 1;
}

template <typename T>
bool Unit<T>::operator==(const Unit &other) const {
  if (strcmp(index, other.index) == 0 && value == other.value) {
    return true;
  }
  return false;
}

template <typename T>
bool Unit<T>::operator!=(const Unit &other) const {
  return operator==(other) ^ 1;
}
