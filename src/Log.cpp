//
// Created by zcy on 2024/12/14.
//

#include "../include/Log.hpp"

#include <iomanip>
#include <iostream>

void Log::cashier(double change) {
  if (change > 0) {
    if (money_.empty()) {
      money_.emplace_back(change, 0);
      return;
    }
    auto tmp = money_.back();
    money_.emplace_back(tmp.first + change, tmp.second);
    return;
  }
  if (money_.empty()) {
    money_.emplace_back(0, change);
    return;
  }
  auto tmp = money_.back();
  money_.emplace_back(tmp.first, tmp.second + change);
}

void Log::show(int count) {
  if (count > money_.size()) {
    throw std::exception();
  }
  if (count == 0) {
    std::cout << '\n';
    return;
  }
  if (count == -1 || count == money_.size()) {
    if (money_.empty()) {
      std::cout << "+ 0.00 - 0.00\n";
    } else {
      auto tmp = money_.back();
      std::cout << std::setprecision(2) << "+ " << tmp.first << " - " << tmp.second << '\n';
    }
    return;
  }
  auto tmp2 = money_.back(), tmp1 = money_[money_.size() - 1 - count];
  std::cout << std::setprecision(2) << "+ " << tmp2.first - tmp1.first << " - " << tmp2.second - tmp1.second << '\n';
}