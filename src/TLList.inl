#pragma once
#include "TLList.h"
#include <exception>
#include <fstream>
#include <iostream>

template<class T>
node<T>::node(T* o) {
  head = new elem<T>(o);
  next = nullptr;
  size = 1;
}

template<class T>
node<T>::node() {
  head = nullptr;
  next = nullptr;
  size = 0;
}

template<class T>
node<T>::~node() {
  while (head != nullptr) {
    elem<T>* tmp = head;
    head = head->next;
    delete tmp;
  }
}

template<typename T>
TLList<T>::TLList() {
  size_ = 0;
  node_head_ = nullptr;
  capacity_ = 10;
}

template<typename T>
TLList<T>::TLList(T* object_ptr_) {
  size_ = 1;
  node_head_ = new node<T>(object_ptr_);
  capacity_ = 10;
}

template<class T>
TLList<T>::TLList(TLList<T> &obj) {
  capacity_ = obj.capacity_;
  node<T>* ntmp2 = obj.node_head_;
  node<T>* ntmp;
  if (ntmp2) {
    ntmp = new node<T>;
    node_head_ = ntmp;
    size_ = 1;
  }
  while (ntmp2) {
    elem<T>* etmp2;
    elem<T>* etmp;
    etmp2 = ntmp2->head;
    if (etmp2) {
      etmp = new elem<T>(etmp2->obj);
      ntmp->head = etmp;
      etmp2 = etmp2->next;
      ntmp->size = 1;
    }
    while (etmp2) {
      etmp->next = new elem<T>(etmp2->obj);
      etmp = etmp->next;
      etmp2 = etmp2->next;
      ntmp->size++;
    }
    ntmp2 = ntmp2->next;
    if (ntmp2) {
      ntmp->next = new node<T>;
      ntmp = ntmp->next;
      size_++;
    }
  }
}

template<typename T>
TLList<T>::~TLList() {
  node<T>* ntmp = node_head_;
  while (ntmp != nullptr) {
    node<T>* ntmp2 = ntmp;
    ntmp = ntmp->next;
    delete ntmp2;
  }
}

template<class T>
T* TLList<T>::getElem(uint list_num, uint elem_pos) {
  return getItem(list_num, elem_pos)->obj;
}

template<class T>
uint TLList<T>::getSize() {
  return size_;
}

template<class T>
uint TLList<T>::getListSize(uint list_num) {
  return getNode(list_num)->size;
}

template<class T>
void TLList<T>::add(T* obj) {
  if (!node_head_) {
    node_head_ = new node<T>(obj);
    size_++;
  } else {
    node<T>* ntmp = node_head_;
    while (ntmp->size >= capacity_ && ntmp->next) ntmp = ntmp->next;
    if (ntmp->size < capacity_) {
      elem<T>* etmp = ntmp->head;
      if (!etmp) {
        etmp = new elem<T>(obj);
        ntmp->head = etmp;
        ntmp->size++;
      } else {
        while (etmp->next) etmp = etmp->next;
        etmp->next = new elem<T>(obj);
        ntmp->size++;
      }
    } else {
      ntmp->next = new node<T>(obj);
      size_++;
    }
  }
}

template<class T>
void TLList<T>::addList() {
  if (!node_head_) {
    node_head_ = new node<T>;
  } else {
    node<T>* ntmp = node_head_;
    while (ntmp->next) ntmp = ntmp->next;
    ntmp->next = new node<T>;
  }
  size_++;
}

template<class T>
void TLList<T>::insertList(uint pos) {
  if (pos > size_)
    throw out_of_range("N/A INDEX");
  if (pos == 0) {
    node<T>* ntmp = node_head_;
    node_head_ = new node<T>;
    node_head_->next = ntmp;
  } else {
    node<T>* ntmp = node_head_;
    for (uint i = 0; i < pos - 1; i++) ntmp = ntmp->next;
    node<T>* ntmp2 = ntmp->next;
    ntmp->next = new node<T>;
    ntmp->next->next = ntmp2;
  }
  size_++;
}

template<class T>
void TLList<T>::removeList(uint pos) {
  if (pos >= size_)
    throw out_of_range("N/A INDEX");
  if (pos == 0) {
    node<T>* ntmp = node_head_->next;
    delete node_head_;
    node_head_ = ntmp;
  } else {
    node<T>* ntmp = node_head_;
    for (uint i = 0; i < pos - 1; i++) ntmp = ntmp->next;
    node<T>* ntmp2 = ntmp->next;
    ntmp->next = ntmp->next->next;
    delete ntmp2;
  }
  size_--;
}

template<class T>
void TLList<T>::remove(uint list_num, uint elem_pos) {
  if (list_num >= size_ || elem_pos >= capacity_)
    throw out_of_range("N/A INDEX");
  node<T>* ntmp = node_head_;
  for (uint i = 0; i < list_num; i++) ntmp = ntmp->next;
  if (elem_pos >= ntmp->size)
    throw out_of_range("N/A INDEX");
  if (elem_pos == 0) {
    elem<T>* etmp = ntmp->head;
    ntmp->head = ntmp->head->next;
    delete etmp;
  } else {
    elem<T>* etmp = ntmp->head;
    for (uint i = 0; i < elem_pos - 1; i++) etmp = etmp->next;
    elem<T>* etmp2 = etmp->next;
    etmp->next = etmp->next->next;
    delete etmp2;
  }
  ntmp->size--;
}

template<class T>
void TLList<T>::insert(uint list_num, uint elem_pos, T* obj) {
  if (list_num >= size_ || elem_pos >= capacity_)
    throw out_of_range("N/A INDEX");
  node<T>* ntmp = node_head_;
  for (uint i = 0; i < list_num; i++) ntmp = ntmp->next;
  if (elem_pos > ntmp->size)
    throw out_of_range("N/A INDEX");
  if (ntmp->size == capacity_)
    throw overflow_error("ELEMENTS OVERFLOW");
  elem<T>* etmp2 = new elem<T>(obj);
  if (elem_pos == 0) {
    etmp2->next = ntmp->head;
    ntmp->head = etmp2;
  } else {
    elem<T>* etmp = ntmp->head;
    for (uint i = 0; i < elem_pos - 1; i++) etmp = etmp->next;
    etmp2->next = etmp->next;
    etmp->next = etmp2;
  }
  ntmp->size++;
}

template<class T>
void TLList<T>::sortLists() {
  node<T>* ntmp = node_head_;
  int node_id = 0;
  while (ntmp) {
    uint num = 0;
    while (num < ntmp->size) {
      uint ct = 0;
      elem<T>* etmp = ntmp->head;
      while (etmp->next) {
        if (*(etmp->obj) > *(etmp->next->obj))
          swap(node_id, ct);
        else
          etmp = etmp->next;
        ct++;
      }
      num++;
    }
    node_id++;
    ntmp = ntmp->next;
  }
}

template<class T>
void TLList<T>::orderedAdd(T* obj) {
  add(obj);
  sortLists();
}

template<class T>
void TLList<T>::orderedInsert(uint list_num, T* obj) {
  insert(list_num, 0, obj);
  sortLists();
}

template<class T>
void TLList<T>::balance() {
  uint sum = 0;
  for (uint i = 0; i < size_; i++) sum += getListSize(i);
  uint n = sum / size_;
  for (uint i = 0; i < size_; i++) {
    if (getListSize(i) >= n) continue;
    for (uint j = 0; j < size_; j++) {
      if (getListSize(j) <= n) continue;
      insert(i, getListSize(i), getItem(j, getListSize(j) - 1)->obj);
      remove(j, getListSize(j) - 1);
    }
  }
  T* buf = new T[sum - (n * size_)];
  int id = 0;
  for (uint i = 0; i < size_; i++)
    while (getListSize(i) > n) {
      buf[id++] = *(getItem(i, n)->obj);
      remove(i, n);
    }
  for (uint i = 0; i < sum - (n * size_); i++) {
    insert(i, n, buf + i);
  }
  delete[] buf;
}

template<class T>
void TLList<T>::resize(uint new_size) {
  bool flag;
  for (uint i = 0; i < size_; i++) {
    flag = true;
    while (getListSize(i) > new_size) {
      if (flag) {
        insertList(i + 1);
        flag = false;
      }
      insert(i + 1, getListSize(i + 1), getItem(i, getListSize(i) - 1)->obj);
      remove(i, getListSize(i) - 1);
    }
  }
  capacity_ = new_size;
}

template<class T>
void TLList<T>::loadToBin(fstream &out) {
  if (out.is_open()) {
    node<T>* ntmp = node_head_;
    elem<T>* etmp;
    while (ntmp) {
      out.write((char*) &(ntmp->size), sizeof(uint));
      etmp = ntmp->head;
      while (etmp) {
        out.write((char*) (etmp->obj), sizeof(T));
        etmp = etmp->next;
      }
      ntmp = ntmp->next;
    }
  }
}

template<class T>
void TLList<T>::loadFromBin(fstream &in) {
  if (in.is_open()) {
    while (node_head_)
      removeList(0);
    node<T>* ntmp;
    if (in.peek() != EOF) {
      node_head_ = ntmp = new node<T>;
      size_ = 1;
    }
    T* tmp = new T;
    uint sz;
    while (in.peek() != EOF) {
      in.read((char*) &sz, sizeof(uint));
      elem<T>* etmp;
      if (sz) {
        in.read((char*) tmp, sizeof(T));
        etmp = new elem<T>(tmp);
        ntmp->head = etmp;
        ntmp->size++;
      }
      for (uint i = 1; i < sz; i++) {
        in.read((char*) tmp, sizeof(T));
        etmp->next = new elem<T>(tmp);
        etmp = etmp->next;
        ntmp->size++;
      }
      ntmp->next = new node<T>;
      ntmp = ntmp->next;
      size_++;
    }
    delete tmp;
  }
}

template<>
void TLList<string>::loadToBin(fstream &out) {
  if (out.is_open()) {
    node<string>* ntmp = node_head_;
    elem<string>* etmp;
    while (ntmp) {
      out.write((char*) &(ntmp->size), sizeof(uint));
      etmp = ntmp->head;
      while (etmp) {
        uint sz = (etmp->obj)->size();
        out.write((char*) &sz, sizeof(sz));
        out.write((char*) (etmp->obj)->c_str(), sizeof(char) * sz);
        etmp = etmp->next;
      }
      ntmp = ntmp->next;
    }
  }
}

template<>
void TLList<string>::loadFromBin(fstream &in) {
  if (in.is_open()) {
    while (node_head_)
      removeList(0);
    node<string>* ntmp;
    if (in.peek() != EOF) {
      node_head_ = ntmp = new node<string>;
      size_ = 1;
    }
    while (in.peek() != EOF) {
      uint lsz, esz;
      in.read((char*) &lsz, sizeof(uint));
      elem<string>* etmp;
      if (lsz) {
        in.read((char*) &esz, sizeof(uint));
        char* tmp = new char[esz+1];
        in.read(tmp, esz);
        tmp[esz] = 0;
        string* str = new string(tmp);
        etmp = new elem<string>(str);
        ntmp->head = etmp;
        ntmp->size++;
        delete str;
        delete[] tmp;
      }
      for (uint i = 1; i < lsz; i++) {
        in.read((char*) &esz, sizeof(uint));
        char* tmp = new char[esz+1];
        in.read(tmp, esz);
        tmp[esz] = 0;
        string* str = new string(tmp);
        etmp->next = new elem<string>(str);
        etmp = etmp->next;
        ntmp->size++;
        delete str;
        delete[] tmp;
      }
      ntmp->next = new node<string>;
      ntmp = ntmp->next;
      size_++;
    }
  }
}

template<class V>
istream &operator>>(istream &is, TLList<V> &tl_list) {
  V* obj = new V;
  is >> *obj;
  tl_list.add(obj);
  delete obj;
  return is;
}

template<class V>
ostream &operator<<(ostream &os, TLList<V> &tl_list) {
  node<V>* ntmp = tl_list.node_head_;
  while (ntmp) {
    elem<V>* etmp = ntmp->head;
    while (etmp) {
      os << *(etmp->obj) << " ";
      etmp = etmp->next;
    }
    ntmp = ntmp->next;
    if (ntmp)
      os << "\n";
  }
  return os;
}

template<class T>
void TLList<T>::swap(uint l, uint p) {
  elem<T>* etmp1 = getItem(l, p);
  elem<T>* etmp2 = getItem(l, p + 1);
  elem<T>* tmp = etmp2->next;
  etmp2->next = etmp1;
  etmp1->next = tmp;
  if (p != 0)
    getItem(l, p - 1)->next = etmp2;
  else
    getNode(l)->head = etmp2;
}

template<class T>
node<T>* TLList<T>::getNode(uint l) {
  node<T>* ntmp = node_head_;
  for (uint i = 0; i < l && ntmp; i++) ntmp = ntmp->next;
  return ntmp;
}

template<class T>
elem<T>* TLList<T>::getItem(uint l, uint p) {
  node<T>* ntmp = node_head_;
  elem<T>* etmp;
  for (uint i = 0; i < l && ntmp; i++) ntmp = ntmp->next;
  if (ntmp) {
    etmp = ntmp->head;
    for (uint i = 0; i < p && etmp; i++) etmp = etmp->next;
  }
  return etmp;
}
