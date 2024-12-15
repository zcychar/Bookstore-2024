//
// Created by zcy on 2024/12/10.
//

#include "../include/Directory.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>

template <typename T>
int Directory<T>::load_dir() {
  int tail = 0;
  dir_.get_info(tail, 3);
  load_.resize(tail + 1);
  dir_.read(load_[1], 3 * sizeof(int), tail);
  return tail;
}

template <typename T>
void Directory<T>::load_cur(int place) {
  cur_.resize(load_[place].size + 1);
  body_.read(cur_[1], load_[place].pos, load_[place].size);
}

template <typename T>
void Directory<T>::new_dir(Unit<T> id) {
  dir_.write_info(1, 1);
  dir_.write_info(1, 2);
  dir_.write_info(1, 3);
  Unit<T> tmp = id;
  tmp.pos = 0;
  tmp.size = 1;
  dir_.update(tmp, 3 * sizeof(int));
  body_.update(id, tmp.pos, tmp.size);
}

template <typename T>
int Directory<T>::insert_find(Unit<T> id) {
  int head = 0;
  dir_.get_info(head, 2);
  int place = 0;
  for (int i = head; i; i = load_[i].next) {
    place = i;
    if (load_[load_[i].next] > id) {
      return place;
    }
  }
  return place;
}

template <typename T>
void Directory<T>::spilt(int place) {
  int tail = 0, sum = 0;
  dir_.get_info(tail, 3);
  dir_.get_info(sum, 1);
  tail++;
  sum++;
  dir_.write_info(sum, 1);
  dir_.write_info(tail, 3);
  int mid = load_[place].size / 2;

  Unit<T> tmp = cur_[mid + 1];
  tmp.pos = (tail - 1) * max_size_ * sizeofU_;
  tmp.size = load_[place].size - mid;
  tmp.next = load_[place].next;
  load_[place].next = tail;
  load_[place].size = mid;

  load_.resize(tail + 1);
  load_[tail] = tmp;
  body_.update(cur_[mid + 1], load_[tail].pos, load_[tail].size);
  body_.update(cur_[1], load_[place].pos, load_[place].size);
  dir_.update(load_[1], 3 * sizeof(int), tail);
}

template <typename T>
void Directory<T>::index_find(int &st, int &ed, Unit<T> id) {
  int head = 0;
  dir_.get_info(head, 2);
  st = head;
  ed = 0;
  for (int i = head; i; i = load_[i].next) {
    int cmp = strcmp(load_[i].index, id.index);
    if (cmp < 0) {
      st = i;
    }
    if (cmp > 0) {
      ed = i;
      break;
    }
  }
}

template <typename T>
void ::Directory<T>::delete_u(int place) {
  int head = 0, sum = 0;
  dir_.get_info(head, 2);
  dir_.get_info(sum, 1);

  if (sum == 1) {
    dir_.write_info(0, 1);
    dir_.write_info(0, 2);
    return;
  }

  if (place == head) {
    head = load_[place].next;
    sum--;
    dir_.write_info(sum, 1);
    dir_.write_info(head, 2);
    return;
  }
  for (int i = head; i; i = load_[i].next) {
    if (load_[i].next == place) {
      sum--;
      load_[i].next = load_[place].next;
      int tail = 0;
      dir_.write_info(sum, 1);
      dir_.get_info(tail, 3);
      dir_.update(load_[1], 3 * sizeof(int), tail);
      return;
    }
  }
}

template <typename T>
Directory<T>::Directory(string file_name, int debug) {
  if (debug) return;
  dir_.initialise(file_name + "_dir.txt");
  body_.initialise(file_name + "_body.txt");
  sizeofU_ = sizeof(Unit<T>);
}

template <typename T>
void Directory<T>::insert(Unit<T> id) {
  int tail = load_dir();
  int sum = 0;
  dir_.get_info(sum, 1);

  if (sum == 0) {
    new_dir(id);
    return;
  }

  int place = insert_find(id);
  load_cur(place);
  auto it = std::upper_bound(cur_.begin() + 1, cur_.begin() + load_[place].size + 1, id);

  // 当前元素不大于第一个 需要更新头节点
  if (it == cur_.begin() + 1) {
    Unit<T> tmp = id;
    tmp.pos = load_[place].pos;
    tmp.next = load_[place].next;
    tmp.size = load_[place].size;
    load_[place] = tmp;
  }
  cur_.emplace(it, id);
  load_[place].size++;
  if (load_[place].size >= limit) {
    spilt(place);
  } else {
    dir_.update(load_[1], 3 * sizeof(int), tail);
    body_.update(cur_[1], load_[place].pos, load_[place].size);
  }
}

template <typename T>
vector<T> Directory<T>::find(Unit<T> id) {
  load_dir();
  int st = 0, ed = 0;
  index_find(st, ed, id);
  vector<T> ans = {};
  for (int i = st; i != ed; i = load_[i].next) {
    load_cur(i);
    auto it = std::lower_bound(cur_.begin() + 1, cur_.begin() + load_[i].size + 1, id);
    while (it != cur_.end() && strcmp(it->index, id.index) == 0) {
      ans.emplace_back(it);
      ++it;
    }
  }
  return ans;
}

template <typename T>
void Directory<T>::del(Unit<T> id) {
  int tail = load_dir();
  int st = 0, ed = 0;
  index_find(st, ed, id);
  for (int i = st; i != ed; i = load_[i].next) {
    load_cur(i);
    auto it = std::lower_bound(cur_.begin() + 1, cur_.begin() + load_[i].size + 1, id);
    int p = it - cur_.begin();
    if (p > load_[i].size) continue;
    if (*it == id) {
      // 如果删除位置为当前块首位，需要更新节点
      if (it == cur_.begin() + 1) {
        // 如果当前块只有1个元素，直接删除块
        if (load_[i].size == 1) {
          delete_u(i);
          return;
        }
        // 否则不改变总块数
        Unit<T> tmp = cur_[2];
        tmp.pos = load_[i].pos;
        tmp.next = load_[i].next;
        tmp.size = load_[i].size;
        load_[i] = tmp;
      }
      cur_.erase(it);
      load_[i].size--;
      dir_.update(load_[1], 3 * sizeof(int), tail);
      body_.update(cur_[1], load_[i].pos, load_[i].size);
      return;
    }
  }
}

template <typename T>
void Directory<T>::print_all() {
  int head = 0, tail = 0;
  dir_.get_info(tail, 3);
  dir_.get_info(head, 2);
  load_.resize(tail + 1);
  dir_.read(load_[1], 3 * sizeof(int), tail);
  for (int i = head; i; i = load_[i].next) {
    cur_.resize(load_[i].size + 1);
    body_.read(cur_[1], load_[i].pos, load_[i].size);
    for (int j = 1; j <= load_[i].size; ++j) {
      std::cout << cur_[j].value << "\n";
    }
  }
}