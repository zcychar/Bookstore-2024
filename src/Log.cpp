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
  if (count == -1) {
    if (money_.empty()) {
      std::cout << "+ 0.00 - 0.00\n";
    } else {
      auto tmp = money_.back();
      std::cout << std::setprecision(2) << std::fixed << "+ " << tmp.first << " - " << -tmp.second << '\n';
    }
    return;
  }
  if (count == 0) {
    std::cout << '\n';
    return;
  }
  if (count > money_.size()) {
    throw std::exception();
  }
  auto tmp2 = money_.back(), tmp1 = money_[money_.size() - 1 - count];
  std::cout << std::setprecision(2) << std::fixed << "+ " << tmp2.first - tmp1.first << " - " << -tmp2.second + tmp1.
      second << '\n';
}

void Log::print_finance() {
  std::cout<<"------------------财务报表-----------------\n";
  std::cout << "|----编号----|----总收入----|----总支出----|\n";
  for (int i = 0; i < money_.size(); ++i) {
    std::cout<<"|";
    std::cout<<std::setfill('-');
    std::cout <<std::right<<std::setw(6)<< i + 1<<"-----|";
    std::cout<<std::setw(10)<<std::setfill('-')<<std::right<< std::setprecision(2) << std::fixed << money_[i].first<<"---|";
    std::cout<<std::setw(10)<<std::setfill('-')<<std::right<< std::setprecision(2) << std::fixed<<money_[i].second <<"---|"<< '\n';
  }
  std::cout<<std::setfill(' ');
}

void Log::print_employee() {
  std::cout<<"--------------------------------------员工报表--------------------------------------\n";
  std::cout<<"id\t\t\t\t\t操作\t\t\t\n";
  for(int i=0;i<log_.size();++i) {
    std::cout<<log_[i].c<<'\n';
  }
}

void Log::print_all() {
  print_employee();
  print_finance();
}

void Log::insert_operation(string name, string opt) {
  log_.emplace_back(statement(name,opt));
}



