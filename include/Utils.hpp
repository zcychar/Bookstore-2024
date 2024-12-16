//
// Created by zcy on 2024/12/15.
//

#ifndef UTILS_HPP
#define UTILS_HPP
#include <vector>
#include <string>

#include "Book.hpp"
using std::string;
using std::vector;

vector<string> parser(string str);

bool isValidString(const std::string &str, int maxmsize);

std::pair<int,string> getInfo(const std::string& str);

double stringtoReal(const std::string &str);

int stringtoInt(const std::string &str);

std::vector<std::string> splitInput(const std::string &input);

Book_info refreshInfo(const vector<string>& str);

#endif //UTILS_HPP