//
// Created by zcy on 2024/12/10.
//

#ifndef UNIT_HPP
#define UNIT_HPP

#include <vector>
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

#endif //UNIT_HPP
