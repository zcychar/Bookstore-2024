//
// Created by zcy on 2024/12/10.
//

#ifndef UNIT_HPP
#define UNIT_HPP

#include <vector>
#include <cstring>
using std::vector;

template <typename T>
struct Unit {
  T value = {};         // 值
  int pos = 0;          // body_文件中头元素位置
  int next = 0;         // 头链表中下一个位置
  int size = 0;         // 作为头结点时 块大小
  char index[80] = {};  // 键

  Unit() = default;

  explicit Unit(const char *str);

  Unit(const char *str, T val);

  bool operator<(const Unit &other) const;

  bool operator>(const Unit &other) const;

  bool operator<=(const Unit &other) const;

  bool operator>=(const Unit &other) const;

  bool operator==(const Unit &other) const;

  bool operator!=(const Unit &other) const;
};
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
  return other.operator<(*this);
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
#endif //UNIT_HPP
