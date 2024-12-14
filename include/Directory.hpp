
#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP
#include <vector>

#include "MemoryRiver.hpp"
#include "Unit.hpp"

using std::vector;

template <typename T>
class Directory {
  const int max_size_ = 1024;
  const int limit = 1000;
  int sizeofU_ = sizeof(Unit<T>);

  MemoryRiver<Unit<T>, 3> dir_;
  MemoryRiver<Unit<T>, 0> body_;

  vector<Unit<T> > load_;
  vector<Unit<T> > cur_;
  // 安全读入dir_
  int load_dir();

  // 安全读入body_
  void load_cur(int place);

  // 当sum=0时调用，创建一个新链表，之前所有数据空间全部可覆盖
  // 对dir_,body_修改，文件内完成io
  void new_dir(Unit<T> id);

  int insert_find(Unit<T> id);

  // 对dir_,body_修改，在函数内完成io
  void spilt(int place);

  void index_find(int &st, int &ed, Unit<T> id);

  // 删除单个节点，废弃对应块
  void delete_u(int place);

 public:
  Directory(string file_name, int debug = 0);
  //修改cur_,load_ 必须输出
  void insert(Unit<T> id);

  void find(Unit<T> id);

  void del(Unit<T> id);
};

#endif //DIRECTORY_HPP
