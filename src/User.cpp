#include "../include/User.hpp"

#include <algorithm>

User::User() { useradd("root", "sjtu", 7, "root"); }

int User::getP() {
  return level_;
}

void User::select(const string ISBN) {
  if(select_.empty()) {
    throw std::exception();
  }
  select_.back()=ISBN;
}

void User::login(string userid, string password) {
  auto tmp = storage_.find(Unit<User_info>(userid.c_str()));
  if (tmp.empty()) {
    throw std::exception();
  }
  auto target = tmp.front();
  if (level_ > target.privilege) {
    login_.push_back(target);
    select_.emplace_back("");
    level_ = target.privilege;
    return;
  }
  if (strcmp(password.c_str(), target.password) == 0) {
    login_.push_back(target);
    select_.emplace_back("");
    level_ = target.privilege;
    return;
  }
  throw std::exception();
}

void User::logout() {
  if (login_.empty()) {
    throw std::exception();
  }
  login_.pop_back();
  select_.pop_back();
  level_ = login_.back().privilege;
}

void User::regist(string userid, string password, string username) {
  auto tmp = storage_.find(Unit<User_info>(userid.c_str()));
  if (!tmp.empty()) {
    throw std::exception();
  }
  storage_.insert(Unit<User_info>(userid.c_str(),
    User_info(userid.c_str(), password.c_str(), username.c_str())));
}

void User::useradd(string userid, string password, int privilege, string username) {
  if(privilege>level_) {
    throw std::exception();
  }
  auto tmp = storage_.find(Unit<User_info>(userid.c_str()));
  if (!tmp.empty()) {
    throw std::exception();
  }
  storage_.insert(Unit<User_info>(userid.c_str(),
    User_info(userid.c_str(), password.c_str(), username.c_str(),privilege)));
}

void User::del(string userid) {
  auto tmp = storage_.find(Unit<User_info>(userid.c_str()));
  if (tmp.empty()) {
    throw std::exception();
  }
  auto target=tmp.front();
  auto it=std::find(login_.begin(),login_.end(),target);
  if(it!=login_.end()) {
    throw std::exception();
  }
  storage_.del(Unit<User_info>(target.user_id,target));
}

void User::passwd(string userid, string currentpassword, string newpassword) {
  auto tmp = storage_.find(Unit<User_info>(userid.c_str()));
  if (tmp.empty()) {
    throw std::exception();
  }
  auto target=tmp.front();
  if(level_!=7&&strcmp(currentpassword.c_str(),target.password)!=0) {
      throw std::exception();
  }
  storage_.del(Unit<User_info>(target.user_id,target));
  memset(target.password,0,sizeof(target.password));
  strcpy(target.password,newpassword.c_str());
  storage_.insert(Unit<User_info>(target.user_id,target));
}

string User::getB() {
  return select_.back();
}

