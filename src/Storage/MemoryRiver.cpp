#include "../../include/Storage/MemoryRiver.hpp"

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