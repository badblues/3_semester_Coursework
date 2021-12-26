#include "TLList.h"

template<typename T>
node<T>::node(T* o) {
  head = new elem<T>(o);
  next = nullptr;
  size = 1;
}

template<typename T>
node<T>::node() {
  head = nullptr;
  next = nullptr;
  size = 0;
}

template<typename T>
node<T>::~node() {
  while (head) {
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
TLList<T>::TLList(T* object_ptr) {
  size_ = 1;
  node_head_ = new node<T>(object_ptr);
  capacity_ = 10;
}

template<typename T>
TLList<T>::~TLList() {
  while (node_head_) {
    node<T>* n_tmp2 = node_head_;
    node_head_ = node_head_->next;
    delete n_tmp2;
  }
}

template<typename T>
T* TLList<T>::getElement(uint list_num, uint elem_pos) {
  return getItem(list_num, elem_pos)->obj;
}

template<typename T>
T* TLList<T>::getElement(uint index) {
  uint l_num = 0;
  for (uint i = 0; i < size_ && index < getListSize(i); i++) {
      index -= getListSize(i);
      l_num++;
  }
  return getItem(l_num, index)->obj;
}

template<typename T>
uint TLList<T>::getSize() {
  return size_;
}

template<typename T>
uint TLList<T>::getCapacity() {
  return capacity_;
}

template<typename T>
uint TLList<T>::getListSize(uint list_num) {
  return getNode(list_num)->size;
}

template<typename T>
void TLList<T>::add(T* obj) {
  if (!node_head_) {
    node_head_ = new node<T>(obj);
    size_++;
  } else {
    for (uint i = 0; i <= size_; i++) {
      if (i == size_) {
        getNode(i - 1)->next = new node<T>(obj);
        size_++;
        break;
      } else if (getListSize(i) < capacity_ && getListSize(i) == 0) {
        getNode(i)->head = new elem<T>(obj);
        getNode(i)->size++;
        break;
      } else if ((getListSize(i) < capacity_ && getListSize(i) > 0)) {
        getItem(i, getListSize(i) - 1)->next = new elem<T>(obj);
        getNode(i)->size++;
        break;
      }
    }
  }
}

template<typename T>
void TLList<T>::addList() {
  if (size_ == 0)
    node_head_ = new node<T>;
  else
    getNode(size_ - 1)->next = new node<T>;
  size_++;
}

template<typename T>
void TLList<T>::insertList(uint pos) {
  if (pos > size_)
    throw out_of_range("N/A INDEX");
  if (pos == 0) {
    node<T>* n_tmp = node_head_;
    node_head_ = new node<T>;
    node_head_->next = n_tmp;
  } else {
    node<T>* n_tmp = getNode(pos - 1);
    node<T>* n_tmp2 = n_tmp->next;
    n_tmp->next = new node<T>;
    n_tmp->next->next = n_tmp2;
  }
  size_++;
}

template<typename T>
void TLList<T>::removeList(uint pos) {
  if (pos >= size_)
    throw out_of_range("N/A INDEX");
  if (pos == 0) {
    node<T>* n_tmp = node_head_->next;
    delete node_head_;
    node_head_ = n_tmp;
  } else {
    node<T>* n_tmp = getNode(pos - 1);
    node<T>* n_tmp2 = n_tmp->next;
    n_tmp->next = n_tmp->next->next;
    delete n_tmp2;
  }
  size_--;
}

template<typename T>
void TLList<T>::remove(uint list_num, uint elem_pos) {
  if (list_num >= size_ || elem_pos >= capacity_)
    throw out_of_range("N/A INDEX");
  node<T>* n_tmp = getNode(list_num);
  if (elem_pos >= n_tmp->size)
    throw out_of_range("N/A INDEX");
  if (elem_pos == 0) {
    elem<T>* e_tmp = n_tmp->head;
    n_tmp->head = n_tmp->head->next;
    delete e_tmp;
  } else {
    elem<T>* e_tmp = getItem(list_num, elem_pos - 1);
    if (!e_tmp->next) {
      delete e_tmp;
    } else {
      elem<T>* e_tmp2 = e_tmp->next;
      e_tmp->next = e_tmp->next->next;
      delete e_tmp2;
    }
  }
  n_tmp->size--;
}

template<typename T>
void TLList<T>::remove(uint index) {
  uint l_num = 0;
  for (uint i = 0; i <= size_ && index >= getListSize(i); i++) {
    if (i == size_)
      throw out_of_range("N/A INDEX");
    index -= getListSize(i);
    l_num++;
  }
  node<T>* n_tmp = getNode(l_num);
  if (index == 0) {
    elem<T>* e_tmp = n_tmp->head;
    n_tmp->head = n_tmp->head->next;
    delete e_tmp;
  } else {
    elem<T>* e_tmp = getItem(l_num, index - 1);
    if (!e_tmp->next) {
      delete e_tmp;
    } else {
      elem<T>* e_tmp2 = e_tmp->next;
      e_tmp->next = e_tmp->next->next;
      delete e_tmp2;
    }
  }
  n_tmp->size--;
}

template<typename T>
void TLList<T>::insert(uint list_num, uint elem_pos, T* obj) {
  if (list_num >= size_ || elem_pos >= capacity_)
    throw out_of_range("N/A INDEX");
  node<T>* n_tmp = getNode(list_num);
  if (elem_pos > n_tmp->size)
    throw out_of_range("N/A INDEX");
  elem<T>* e_tmp2 = new elem<T>(obj);
  if (elem_pos == 0) {
    e_tmp2->next = n_tmp->head;
    n_tmp->head = e_tmp2;
  } else {
    elem<T>* e_tmp = getItem(list_num, elem_pos - 1);
    e_tmp2->next = e_tmp->next;
    e_tmp->next = e_tmp2;
  }
  n_tmp->size++;
  while (n_tmp->size > capacity_) {
    if (!n_tmp->next)
      addList();
    move(list_num, n_tmp->size - 1, list_num + 1, 0);
    list_num++;
    n_tmp = n_tmp->next;
  }
}

template<typename T>
void TLList<T>::insert(uint index, T* obj) {
  uint l_num = 0;
  for (uint i = 0; i <= size_ && index > getListSize(i); i++) {
    if (i == size_)
      throw out_of_range("N/A INDEX");
    index -= getListSize(i);
    l_num++;
  }
  node<T>* n_tmp = getNode(l_num);
  elem<T>* e_tmp2 = new elem<T>(obj);
  if (index == 0) {
    e_tmp2->next = n_tmp->head;
    n_tmp->head = e_tmp2;
  } else {
    elem<T>* e_tmp = n_tmp->head;
    for (uint i = 0; i < index - 1; i++) e_tmp = e_tmp->next;
    e_tmp2->next = e_tmp->next;
    e_tmp->next = e_tmp2;
  }
  n_tmp->size++;
  while (n_tmp->size > capacity_) {
    if (!n_tmp->next)
      addList();
    move(l_num, n_tmp->size - 1, l_num + 1, 0);
    l_num++;
    n_tmp = n_tmp->next;
  }
}

template<typename T>
void TLList<T>::sort() {
  node<T>* n_tmp = node_head_;
  int node_id = 0;
  while (n_tmp) {
    uint num = 0;
    while (num < n_tmp->size) {
      uint ct = 0;
      elem<T>* e_tmp = n_tmp->head;
      while (e_tmp->next) {
        if (*(e_tmp->obj) > *(e_tmp->next->obj))
          swap(node_id, ct);
        else
          e_tmp = e_tmp->next;
        ct++;
      }
      num++;
    }
    node_id++;
    n_tmp = n_tmp->next;
  }
}

template<typename T>
void TLList<T>::orderedAdd(T* obj) {
  add(obj);
  sort();
}

template<typename T>
void TLList<T>::orderedInsert(uint list_num, T* obj) {
  insert(list_num, 0, obj);
  sort();
}

template<typename T>
void TLList<T>::balance() {
  uint sum = 0;
  for (uint i = 0; i < size_; i++) sum += getListSize(i);
  uint n = sum / size_;
  for (uint i = 0; i < size_; i++) {
    for (uint j = 0; j < size_ && getListSize(i) < n; j++) {
      while (getListSize(j) > n)
        move(j, getListSize(j) - 1, i, getListSize(i));
    }
  }
  elem<T>** buf = new elem<T>*[sum - (n * size_)];
  int id = 0;
  for (uint i = 0; i < size_; i++)
    while (getListSize(i) > n) {
      buf[id++] = getItem(i, n);
      if (n == 0)
        getNode(i)->head = getNode(i)->head->next;
      else
        getItem(i, n - 1)->next = getItem(i, n - 1)->next->next;
      getNode(i)->size--;
    }
  for (uint i = 0; i < sum - (n * size_); i++) {
    if (n == 0) {
      getNode(i)->head = buf[i];
      getNode(i)->head->next = nullptr;
    } else {
      getItem(i, n - 1)->next = buf[i];
      getItem(i, n - 1)->next->next = nullptr;
    }
    getNode(i)->size++;
  }
  delete[] buf;
}

template<typename T>
void TLList<T>::resize(uint new_size) {
  if (new_size == 0)
    throw overflow_error("SIZE CANNOT BE EQUAL TO 0");
  bool flag;
  for (uint i = 0; i < size_; i++) {
    flag = true;
    while (getListSize(i) > new_size) {
      if (flag) {
        insertList(i + 1);
        flag = false;
      }
      move(i, getListSize(i) - 1, i + 1, getListSize(i + 1));
    }
  }
  capacity_ = new_size;
}

template<typename T>
void TLList<T>::loadToBin(fstream &out) {
  if (out.is_open()) {
    node<T>* n_tmp = node_head_;
    elem<T>* e_tmp;
    while (n_tmp) {
      out.write((char*) &(n_tmp->size), sizeof(uint));
      e_tmp = n_tmp->head;
      while (e_tmp) {
        out.write((char*) (e_tmp->obj), sizeof(T));
        e_tmp = e_tmp->next;
      }
      n_tmp = n_tmp->next;
    }
  }
}

template<typename T>
void TLList<T>::loadFromBin(fstream &in) {
  if (in.is_open()) {
    while (node_head_)
      removeList(0);
    node<T>* n_tmp;
    if (in.peek() != EOF) {
      node_head_ = n_tmp = new node<T>;
      size_ = 1;
    }
    uint sz;
    T* tmp;
    while (in.peek() != EOF) {
      in.read((char*) &sz, sizeof(uint));
      elem<T>* e_tmp;
      if (sz) {
        tmp = new T;
        in.read((char*) tmp, sizeof(T));
        e_tmp = new elem<T>(tmp);
        n_tmp->head = e_tmp;
        n_tmp->size++;
      }
      for (uint i = 1; i < sz; i++) {
        tmp = new T;
        in.read((char*) tmp, sizeof(T));
        e_tmp->next = new elem<T>(tmp);
        e_tmp = e_tmp->next;
        n_tmp->size++;
      }
      n_tmp->next = new node<T>;
      n_tmp = n_tmp->next;
      size_++;
    }
  }
}

template<>
void TLList<string>::loadToBin(fstream &out) {
  if (out.is_open()) {
    node<string>* n_tmp = node_head_;
    elem<string>* e_tmp;
    while (n_tmp) {
      out.write((char*) &(n_tmp->size), sizeof(uint));
      e_tmp = n_tmp->head;
      while (e_tmp) {
        uint sz = (e_tmp->obj)->size();
        out.write((char*) &sz, sizeof(sz));
        out.write((char*) (e_tmp->obj)->c_str(), sizeof(char) * sz);
        e_tmp = e_tmp->next;
      }
      n_tmp = n_tmp->next;
    }
  }
}

template<>
void TLList<string>::loadFromBin(fstream &in) {
  if (in.is_open()) {
    while (node_head_)
      removeList(0);
    node<string>* n_tmp;
    if (in.peek() != EOF) {
      n_tmp = new node<string>;
      node_head_ = n_tmp;
      size_ = 1;
    }
    while (in.peek() != EOF) {
      uint lsz, esz;
      in.read((char*) &lsz, sizeof(uint));
      elem<string>* e_tmp;
      if (lsz) {
        in.read((char*) &esz, sizeof(uint));
        char* tmp = new char[esz + 1];
        in.read(tmp, esz);
        tmp[esz] = 0;
        string* str = new string(tmp);
        e_tmp = new elem<string>(str);
        n_tmp->head = e_tmp;
        n_tmp->size++;
        delete[] tmp;
      }
      for (uint i = 1; i < lsz; i++) {
        in.read((char*) &esz, sizeof(uint));
        char* tmp = new char[esz + 1];
        in.read(tmp, esz);
        tmp[esz] = 0;
        string* str = new string(tmp);
        e_tmp->next = new elem<string>(str);
        e_tmp = e_tmp->next;
        n_tmp->size++;
        delete[] tmp;
      }
      if (in.peek() != EOF) {
        n_tmp->next = new node<string>;
        n_tmp = n_tmp->next;
        size_++;
      }
    }
  }
}

template<typename T>
void TLList<T>::swap(uint l, uint p) {
  elem<T>* e_tmp1 = getItem(l, p);
  elem<T>* e_tmp2 = getItem(l, p + 1);
  elem<T>* tmp = e_tmp2->next;
  e_tmp2->next = e_tmp1;
  e_tmp1->next = tmp;
  if (p != 0)
    getItem(l, p - 1)->next = e_tmp2;
  else
    getNode(l)->head = e_tmp2;
}

template<typename T>
void TLList<T>::move(uint l1, uint p1, uint l2, uint p2) {
  if (l1 >= size_ || l2 >= size_)
    throw out_of_range("N/A INDEX");
  node<T>* n_tmp1 = getNode(l1);
  node<T>* n_tmp2 = getNode(l2);
  if (p1 >= n_tmp1->size || p2 > n_tmp2->size)
    throw out_of_range("N/A INDEX");
  elem<T>* e_tmp;
  elem<T>* e_tmp2;
  if (p1 == 0) {
    e_tmp = n_tmp1->head;
    n_tmp1->head = n_tmp1->head->next;
  } else {
    e_tmp = getItem(l1, p1);
    e_tmp2 = getItem(l1, p1 - 1);
    e_tmp2->next = e_tmp2->next->next;
  }
  n_tmp1->size--;
  if (p2 == 0) {
    e_tmp->next = n_tmp2->head;
    n_tmp2->head = e_tmp;
  } else {
    e_tmp2 = getItem(l2, p2 - 1);
    e_tmp->next = e_tmp2->next;
    e_tmp2->next = e_tmp;
  }
  n_tmp2->size++;
}

template<typename T>
node<T>* TLList<T>::getNode(uint l) {
  node<T>* n_tmp = node_head_;
  for (uint i = 0; i < l && n_tmp; i++) n_tmp = n_tmp->next;
  return n_tmp;
}

template<typename T>
elem<T>* TLList<T>::getItem(uint l, uint p) {
  node<T>* n_tmp = node_head_;
  elem<T>* e_tmp = nullptr;
  for (uint i = 0; i < l && n_tmp; i++) n_tmp = n_tmp->next;
  if (n_tmp) {
    e_tmp = n_tmp->head;
    for (uint i = 0; i < p && e_tmp; i++) e_tmp = e_tmp->next;
  }
  return e_tmp;
}
template<class T>
T &TLList<T>::operator[](uint index) {
  uint l_num = 0;
  for (uint i = 0; i < size_ && index >= getListSize(i); i++) {
      index -= getListSize(i);
      l_num++;
  }
  return *(getItem(l_num, index)->obj);
}

template
class TLList<int>;

template
class TLList<float>;

template
class TLList<double>;

template
class TLList<char>;

template
class TLList<unsigned int>;

template
class TLList<long>;

template
class TLList<long long>;

template
class TLList<short>;

template
class TLList<string>;
