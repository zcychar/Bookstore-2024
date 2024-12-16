#ifndef BPT_MEMORYRIVER_HPP
#define BPT_MEMORYRIVER_HPP

#include <unistd.h>

#include <fstream>

using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;

template <class T, int info_len = 2>
class MemoryRiver {
 private:
  /* your code here */
  fstream file;
  string file_name;
  int sizeofT = sizeof(T);

 public:
  MemoryRiver() = default;

  MemoryRiver(const string &file_name) : file_name(file_name) {}

  void initialise(string FN = "");

  // 读出第n个int的值赋给tmp，1_base
  void get_info(int &tmp, int n);

  // 将tmp写入第n个int的位置，1_base
  void write_info(int tmp, int n);

  // 在文件合适位置写入类对象t，并返回写入的位置索引index
  // 位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
  // 位置索引index可以取为对象写入的起始位置
  int write(T &t, int size = 1);

  // 用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
  void update(T &t, const int index,int size=1);

  //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
  void read(T &t, const int index,int size=1);

  //删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)，保证调用的index都是由write函数产生
  void Delete(int index);
};

template <class T, int info_len>
void MemoryRiver<T, info_len>::initialise(string FN) {
  if (FN != "") file_name = FN;
  if (access(file_name.c_str(), F_OK) == 0) {
    return;
  }
  file.open(file_name, std::ios::out);
  int tmp = 0;
  for (int i = 0; i < info_len; ++i) file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
  file.close();
}

template <class T, int info_len>
void MemoryRiver<T, info_len>::get_info(int &tmp, int n) {
  if (n > info_len) return;
  file.open(file_name);
  file.seekg((n - 1) * sizeof(int));
  file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
  file.close();
}

template <class T, int info_len>
void MemoryRiver<T, info_len>::write_info(int tmp, int n) {
  if (n > info_len) return;
  file.open(file_name);
  file.seekp((n - 1) * sizeof(int));
  file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
  file.close();
}

template <class T, int info_len>
int MemoryRiver<T, info_len>::write(T &t, int size) {
  file.open(file_name, std::ios::app);
  int index = file.tellp();
  file.write(reinterpret_cast<char *>(&t), sizeofT * size);
  file.close();
  return index;
}

template <class T, int info_len>
void MemoryRiver<T, info_len>::update(T &t, const int index, int size) {
  file.open(file_name);
  file.seekp(index);
  file.write(reinterpret_cast<char *>(&t), sizeofT * size);
  file.close();
}

template <class T, int info_len>
void MemoryRiver<T, info_len>::read(T &t, const int index, int size) {
  file.open(file_name);
  file.seekg(index);
  file.read(reinterpret_cast<char *>(&t), sizeofT * size);
  file.close();
}
#endif //BPT_MEMORYRIVER_HPP