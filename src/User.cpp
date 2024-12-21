#include "../include/User.hpp"

#include <algorithm>

User::User() {
  auto tmp = storage_.find(Unit<User_info>("root"));
  if (tmp.empty()) {
    storage_.insert(Unit<User_info>("root",User_info("root","sjtu","root",7)));
  }
}

int User::getP() {
  return level_;
}

void User::deep_select(string ISBN,string ISBN_old) {
  for(int i=0;i<select_.size();++i) {
    if(select_[i]==ISBN_old) {
      select_[i]=ISBN;
    }
  }
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
    throw std::runtime_error("11");
  }
  auto target = tmp.front();
  if(!password.empty()&&strcmp(password.c_str(), target.password)!=0) {
    throw std::runtime_error("11");
  }
  if (level_ > target.privilege) {
    login_.push_back(target);
    select_.emplace_back("");
    level_ = target.privilege;
    return;
  }
  if (!password.empty()) {
    login_.push_back(target);
    select_.emplace_back("");
    level_ = target.privilege;
    return;
  }
  throw std::runtime_error("11");
}

void User::logout() {
  if (login_.empty()) {
    throw std::exception();
  }
  login_.pop_back();
  select_.pop_back();
  if(login_.empty()) {
    level_=0;
  }else {
    level_ = login_.back().privilege;
  }

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
  if(privilege>=level_) {
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

void User::passwd(string userid, string newpassword, string currentpassword) {
  auto tmp = storage_.find(Unit<User_info>(userid.c_str()));
  if (tmp.empty()) {
    throw std::exception();
  }
  auto target=tmp.front();
  if(currentpassword!=""&&strcmp(currentpassword.c_str(),target.password)!=0) {
      throw std::exception();
  }
  if(currentpassword==""&&level_!=7) {
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

