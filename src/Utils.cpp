//
// Created by zcy on 2024/12/15.
//

#include "../include/Utils.hpp"

#include <set>


vector<string> parser(string str) {
  vector<string>tmp={};
  std::set<string>common={};
  string s="";
  for(int i=0;i<str.length();++i) {
    if(!isprint(str[i])||str[i]=='"') {
      throw std::exception();
    }
    if(str[i]=='|') {
      if(s.empty()) {
        throw std::exception();
      }
      if(common.insert(s).second==false) {
        throw std::exception();
      }
      s="";
    }else {
      s+=str[i];
    }
  }
  if(!s.empty()) {
    if(common.insert(s).second==false) {
      throw std::exception();
    }
  }
  for(const auto& it:common) {
    tmp.push_back(it);
  }
  return tmp;
}
