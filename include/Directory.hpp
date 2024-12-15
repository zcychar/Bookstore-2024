/*File:Directory.hpp
 *------------------
 *实现了键-值文件存储系统，使用块状链表，链表部分和数据块分别存储在外部存储文件中
 *实现单点插入，单点删除，按键查找功能
 *@note 键为不超过64位字符串
 *@note 值需要定义比较符号和输出，并且不涉及动态空间
 *调用方式:Directory<Value>(file_name)
 *@func:insert(Unit<Value>(index,Value))
 *@func:
 */
#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP
#include <vector>

#include "Storage/MemoryRiver.hpp"
#include "Storage/Unit.hpp"

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

  // 对dir_,body_修改
  void spilt(int place);

  //按键查找辅助函数,返回查找范围
  void index_find(int &st, int &ed, Unit<T> id);

  // 删除单个节点，废弃对应块
  void delete_u(int place);

 public:
  explicit Directory(string file_name, int debug = 0);
  //修改cur_,load_ 必须输出
  void insert(Unit<T> id);
  //查找并按键从小到大输出
  vector<T> find(Unit<T> id);
  //单点删除
  void del(Unit<T> id);

  void print_all();
};

#endif //DIRECTORY_HPP
