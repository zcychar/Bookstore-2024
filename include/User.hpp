//
// Created by zcy on 2024/12/14.
//

#ifndef USER_HPP
#define USER_HPP

#include <cstring>
#include <vector>

#include "Directory.hpp"

using std::vector;
using std::string;

struct User_info {
  char user_id[40] = {};
  char user_name[40] = {};
  char password[40] = {};
  int privilege = 0;

  User_info() = default;

  User_info(const User_info& other) {
    memset(user_id, 0, sizeof(user_id));
    memset(user_name, 0, sizeof(user_name));
    memset(password, 0, sizeof(password));
    strcpy(user_id, other.user_id);
    strcpy(user_name, other.user_name);
    strcpy(password, other.password);
    privilege = other.privilege;
  }

  User_info(const char *userid, const char *passwrd, const char *username, const int pri = 1) {
    memset(user_id, 0, sizeof(user_id));
    memset(user_name, 0, sizeof(user_name));
    memset(password, 0, sizeof(password));
    strcpy(user_id, userid);
    strcpy(user_name, username);
    strcpy(password, passwrd);
    privilege = pri;
  }

  bool operator<(const User_info &other) const { return (strcmp(user_id, other.user_id) == -1); }

  bool operator==(const User_info &other) const {
    return (strcmp(user_id, other.user_id) == 0) && (strcmp(password, other.password)==0);
  }

  bool operator>(const User_info &other) const { return operator<(other) ^ 1; }
};

class User {
  Directory<User_info> storage_ =Directory<User_info>("user_storage");
  vector<User_info> login_ = {};
  vector<string>select_={};
  int level_ = 0;


public:
  User();

 void deep_select(string ISBN,string ISBN_old);

  int getP();

  void select(string ISBN);

  void login(string userid, string password = {});

  void logout();

  void regist(string userid, string password, string username);

  void passwd(string userid, string newpassword, string currentpassword="");

  void useradd(string userid, string password, int privilege, string username,int initial=0);

  void del(string userid);

  string getB();
};

#endif  // USER_HPP