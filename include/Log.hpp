#ifndef LOG_HPP
#define LOG_HPP
#include "Directory.hpp"
#include "Storage/MemoryRiver.hpp"


class Log {
  vector<std::pair<double, double> > money_;
  MemoryRiver<std::pair<double, double>, 1> storage_;

public:
  Log() {
    storage_.initialise("finance.txt");
    int len = 0;
    storage_.get_info(len, 1);
    money_.resize(len);
    storage_.read(money_[0], sizeof(int), len);
  }

  void exit() {
    int len = money_.size();
    storage_.write_info(len, 1);
    storage_.update(money_[0], sizeof(int), len);
  }

  void cashier(double change);

  void show(int count);
};


#endif //LOG_HPP