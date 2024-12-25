//
// Created by zcy on 2024/12/15.
//

#include "../include/Utils.hpp"

#include <sstream>
#include <istream>
#include <set>


vector<string> parser(string str) {
  vector<string> tmp = {};
  std::set<string> common = {};
  string s = "";
  for (int i = 0; i < str.length(); ++i) {
    if (!isprint(str[i]) || str[i] == '"') {
      throw std::exception();
    }
    if (str[i] == '|') {
      if (s.empty()) {
        throw std::exception();
      }
      if (common.insert(s).second == false) {
        throw std::exception();
      }
      s = "";
    } else {
      s += str[i];
    }
  }
  if (!s.empty()) {
    if (common.insert(s).second == false) {
      throw std::exception();
    }
  }
  for (const auto &it : common) {
    tmp.push_back(it);
  }
  return tmp;
}

bool isValidString(const std::string &str, int maxmlength) {
  if (str.size() > maxmlength) {
    return false;
  }
  for (char ch : str) {
    if (!(std::isalnum(ch) || ch == '_')) {
      // 检查是否是字母、数字或下划线
      return false;
    }
  }
  return true;
}
//type:1-ISBN,2-name,3-author,4-keyword,5-price
std::pair<int, string> getInfo(const std::string &str) {
  switch (str[1]) {
    case 'I': {
      if (str.substr(0, 6) != "-ISBN=") {
        throw std::exception();
      }
      string tmp = str.substr(6);
      if(!isValidName(tmp,20)||tmp.empty()) {
        throw std::exception();
      }
      return std::make_pair(1, tmp);
    }
    case 'n': {
      if (str.substr(0, 7) != "-name=\"" || str[str.size() - 1] != '"') {
        throw std::exception();
      }
      string tmp = str.substr(7);
      tmp.pop_back();
      for(auto i:tmp) {
        if(i=='"') {
          throw std::exception();
        }
      }
      if(!isValidName(tmp,60)||tmp.empty()) {
        throw std::exception();
      }
      return std::make_pair(2, tmp);
    }
    case 'a': {
      if (str.substr(0, 9) != "-author=\"" || str[str.size() - 1] != '"') {
        throw std::exception();
      }
      string tmp = str.substr(9);
      tmp.pop_back();
      for(auto i:tmp) {
        if(i=='"') {
          throw std::exception();
        }
      }
      if(!isValidName(tmp,60)||tmp.empty()) {
        throw std::exception();
      }
      return std::make_pair(3, tmp);
    }
    case 'k': {
      if (str.substr(0, 10) != "-keyword=\"" || str[str.size() - 1] != '"') {
        throw std::exception();
      }
      string tmp = str.substr(10);
      tmp.pop_back();
      for(auto i:tmp) {
        if(i=='"') {
          throw std::exception();
        }
      }
      if(!isValidName(tmp,60)||tmp.empty()) {
        throw std::exception();
      }
      return std::make_pair(4, tmp);
    } case 'p': {
      if (str.substr(0, 7) != "-price=") {
        throw std::exception();
      }
      string tmp = str.substr(7);
      if(tmp.empty()||tmp.size()>13) {
        throw std::exception();
      }
      stringtoReal(tmp);
      return std::make_pair(5, tmp);
    }
    default: {
      throw std::exception();
    }
  }
}


double stringtoReal(const std::string &str) {
  if(str.size()>13||str[0]=='.') {
    throw std::exception();
  }
  std::istringstream stream(str);
  double value;
  stream >> value;
  if (!stream.eof()) stream >> std::ws;
  if (stream.fail() || !stream.eof()) {
    throw std::exception();
  }
  return value;
}

std::vector<std::string> splitInput(const std::string &input) {
  std::vector<std::string> result={};
  std::string word;
  for(const char ch:input) {
    if(ch==' ') {
      if(!word.empty()) {
        result.push_back(word);
      }
      word.clear();
    }else {
      word+=ch;
    }
  }
  if(!word.empty()) {
    result.push_back(word);
  }
  return result;
}

int stringtoInt(const std::string &str) {
  if(str.length()>10||str[0]=='0') {
    throw std::exception();
  }
  std::istringstream stream(str);
  long long value;
  stream >> value;
  if (!stream.eof()) stream >> std::ws;
  if (stream.fail() || !stream.eof()) {
    throw std::exception();
  }
  if(value>2147483647) {
    throw std::exception();
  }
  return value;
}
//type:1-ISBN,2-name,3-author,4-keyword,5-price
Book_info refreshInfo(const vector<string>& str) {
  Book_info val;
  bool changed[6]={false,false,false,false,false,false};
  for(int i=1;i<str.size();++i) {
     auto tmp=getInfo(str[i]);
     switch(tmp.first) {
       case 1: {
         if(changed[1]) {
           throw std::exception();
         }
         changed[1]=true;
         memset(val.ISBN,0,sizeof(val.ISBN));
         strcpy(val.ISBN,tmp.second.c_str());
         break;
       }
       case 2: {
         if(changed[2]) {
           throw std::exception();
         }
         changed[2]=true;
         memset(val.bookname,0,sizeof(val.bookname));
         strcpy(val.bookname,tmp.second.c_str());
         break;
       }
       case 3: {
         if(changed[3]) {
           throw std::exception();
         }
         changed[3]=true;
         memset(val.author,0,sizeof(val.author));
         strcpy(val.author,tmp.second.c_str());
         break;
       }
       case 4: {
         if(changed[4]) {
           throw std::exception();
         }
         changed[4]=true;
         memset(val.keyword,0,sizeof(val.keyword));
         strcpy(val.keyword,tmp.second.c_str());
         break;
       }
       case 5: {
         if(changed[5]) {
           throw std::exception();
         }
         changed[5]=true;
         val.price=stringtoReal(tmp.second);
         break;
       }
       default: {
         throw std::exception();
       }
     }
  }
  return val;
}

bool isValidName(const std::string &str, int maxmsize) {
    if (str.size() > maxmsize||str.empty()) {
      return false;
    }
    for (char ch : str) {
      if (ch<32||ch>126) {
        // 检查是否是不可见字符
        return false;
      }
    }
    return true;
}

bool isValidPri(const std::string &str) {
  if (str.size() > 1) {
    return false;
  }
  for (char ch : str) {
    if (ch<'0'||ch>'9') {
      // 检查是否是数字
      return false;
    }
  }
  return true;
}
