#ifndef LOG_HPP
#define LOG_HPP
#include "Directory.hpp"


class Log {
  vector<std::pair<double, double> > money_;

public:
  void cashier(double change);

  void show(int count);
};


#endif //LOG_HPP