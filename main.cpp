#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include "include/Book.hpp"
#include "include/Log.hpp"
#include "include/User.hpp"
#include "include/Utils.hpp"

void processLine(string &input, User &user, Log &log, Book &book) {
  auto processed = splitInput(input);
  if (processed.empty())return;
  string opt = processed[0];
  int current_level = user.getP();
  if (opt == "quit" || opt == "exit") {
    if (processed.size() != 1) {
      throw std::exception();
    }
    log.exit();
    exit(0);
  }
  if (opt == "su") {
    if (processed.size() == 2) {
      if (!isValidString(processed[1], 30)) {
        throw std::exception();
      }
      user.login(processed[1]);
    } else if (processed.size() == 3) {
      if (!isValidString(processed[1], 30) || !isValidString(processed[2], 30)) {
        throw std::exception();
      }
      user.login(processed[1], processed[2]);
    } else {
      throw std::exception();
    }
  } else if (opt == "logout") {
    if (current_level < 1 || processed.size() > 1) {
      throw std::exception();
    }
    user.logout();
  } else if (opt == "register") {
    if (processed.size() != 4) {
      throw std::exception();
    }
    if (!isValidString(processed[1], 30) || !isValidString(processed[2], 30) || processed[3].size() > 30) {
      throw std::exception();
    }
    user.regist(processed[1], processed[2], processed[3]);
  } else if (opt == "passwd") {
    if (current_level < 1) {
      throw std::exception();
    }
    if (processed.size() == 3) {
      if (!isValidString(processed[1], 30) || !isValidString(processed[2], 30)) {
        throw std::exception();
      }
      user.passwd(processed[1], processed[2]);
    } else if (processed.size() == 4) {
      if (!isValidString(processed[1], 30) || !isValidString(processed[2], 30) || !isValidString(processed[3], 30)) {
        throw std::exception();
      }
      user.passwd(processed[1], processed[3], processed[2]);
    } else {
      throw std::exception();
    }
  } else if (opt == "useradd") {
    if (current_level < 3 || processed.size() != 5) {
      throw std::exception();
    }
    if (!isValidString(processed[1], 30) || !isValidString(processed[2], 30) || !isValidName(processed[4], 30) || !
        isValidPri(processed[3])) {
      throw std::exception();
    }
    int pri = stringtoInt(processed[3]);
    if (pri != 1 && pri != 3 && pri != 7) {
      throw std::exception();
    }
    user.useradd(processed[1], processed[2], pri, processed[4]);
  } else if (opt == "delete") {
    if (current_level < 7 || processed.size() != 2 || !isValidString(processed[1], 30)) {
      throw std::exception();
    }
    user.del(processed[1]);
  } else if (opt == "show") {
    if (processed[1] == "finance") {
      if (current_level < 7) {
        throw std::exception();
      }
      if (processed.size() == 2) {
        log.show(-1);
      } else if (processed.size() == 3) {
        int tmp = stringtoInt(processed[2]);
        if (tmp < 0) {
          throw std::exception();
        }
        log.show(stringtoInt(processed[2]));
      } else {
        throw std::exception();
      }
    } else {
      //type:0-all,1-ISBN,2-name,3-author,4-keyword
      if (current_level < 1) {
        throw std::exception();
      }
      if (processed.size() == 1) {
        book.show(0);
      } else if (processed.size() == 2) {
        auto tmp = getInfo(processed[1]);
        book.show(tmp.first, tmp.second);
      } else {
        throw std::exception();
      }
    }
  } else if (opt == "buy") {
    if (processed.size() != 3 || current_level < 1 || !isValidName(processed[1], 20)) {
      throw std::exception();
    }
    int quan = stringtoInt(processed[2]);
    if (quan <= 0) {
      throw std::exception();
    }
    auto price = book.buy(processed[1], quan);
    double spend = quan * 1.0 * price;
    std::cout << std::setprecision(2) << std::fixed << spend << '\n';
    log.cashier(spend);
  } else if (opt == "select") {
    if (processed.size() != 2 || !isValidName(processed[1], 20) || current_level < 3) {
      throw std::exception();
    }
    book.create(processed[1]);
    user.select(processed[1]);
  } else if (opt == "modify") {
    if (processed.size() == 1 || current_level < 3) {
      throw std::exception();
    }
    auto old = user.getB();
    if (old.empty()) {
      throw std::exception();
    }
    auto tmp = refreshInfo(processed);
    if (tmp.keyword[0] != 0) {
      parser(string(tmp.keyword));
    }
    book.modify(tmp, old);
    if (tmp.ISBN[0] != 0) {
      user.deep_select(string(tmp.ISBN), old);
    }
  } else if (opt == "import") {
    if (processed.size() != 3 || current_level < 3) {
      throw std::exception();
    }
    double total = stringtoReal(processed[2]);
    int quan = stringtoInt(processed[1]);
    if (total <= 0 || quan <= 0) {
      throw std::exception();
    }
    book.import(user.getB(), quan);
    log.cashier(-total);
  } else if (opt == "log") {
    if (processed.size() != 1 || current_level < 7) {
      throw std::exception();
    }
    log.print_all();
  } else if (opt == "report") {
    if (processed.size() != 2 || current_level < 7) {
      throw std::exception();
    }
    if (processed[1] != "finance" && processed[1] != "employee") {
      throw std::exception();
    }
    if (processed[1] == "finance") {
      log.print_finance();
    }
    if (processed[1] == "employee") {
      log.print_employee();
    }
  } else {
    throw std::exception();
  }
}

int main() {
  Book book;
  Log log;
  User user;

  std::string input;
  while (getline(std::cin, input)) {
    try {
      if (!input.empty()) {
        processLine(input, user, log, book);
        log.insert_operation(user.getName(), input);
      }
    } catch (...) {
      std::cout << "Invalid\n";
    }
  }
  log.exit();
  return 0;
}