#ifndef LOG_HPP
#define LOG_HPP
#include "Directory.hpp"
#include "Storage/MemoryRiver.hpp"

struct statement {
  char c[400]{};

  statement(string name, string opt) {
    auto tmp = name + "\t\t\t\t" + opt;
    memset(c, 0, sizeof(c));
    memcpy(c, tmp.c_str(), sizeof(c));
  }

  statement() = default;
};

class Log {
  vector<std::pair<double, double> > money_;
  MemoryRiver<std::pair<double, double>, 1> storage_;
  MemoryRiver<statement> log_storage_;
  vector<statement> log_;

public:
  Log() {
    storage_.initialise("finance.txt");
    int len = 0;
    storage_.get_info(len, 1);
    money_.resize(len);
    storage_.read(money_[0], sizeof(int), len);
    log_storage_.initialise("log.txt");
    int len1 = 0;
    log_storage_.get_info(len1, 1);
    log_.resize(len1);
    log_storage_.read(log_[0], sizeof(int), len1);
  }

  void exit() {
    int len = money_.size();
    storage_.write_info(len, 1);
    storage_.update(money_[0], sizeof(int), len);
    int len1 = log_.size();
    log_storage_.write_info(len1, 1);
    log_storage_.update(log_[0], sizeof(int), len1);
  }

  void cashier(double change);

  void show(int count);

  void print_finance();

  void print_all();

  void print_employee();

  void insert_operation(string name, string operation);
};


#endif //LOG_HPP