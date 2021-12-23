#pragma once
#include <iostream>
#include <string>
#include <exception>
#include <fstream>

using namespace std;
typedef unsigned int uint;

// TLLIST for TwoLevelledList

template<typename T>
struct elem {
  T* obj;
  struct elem* next;
  explicit elem(T* o) {
    obj = new T;
    *obj = *o;
    next = nullptr;
  }
  ~elem() { delete obj; }
};

template<typename T>
struct node {
  elem<T>* head;
  struct node* next;
  uint size;
  explicit node(T* o);
  node();
  ~node();
};

template<typename T>
class TLList {
  public:
  TLList();
  explicit TLList(T* object_ptr);
  TLList(TLList<T> &obj);
  ~TLList();
  T* getElement(uint list_num, uint elem_pos);
  uint getSize();
  uint getCapacity();
  uint getListSize(uint list_num);
  void add(T* obj);
  void addList();
  void insertList(uint pos);
  void removeList(uint pos);
  void remove(uint list_num, uint elem_pos);
  void insert(uint list_num, uint elem_pos, T* obj);
  void sort();
  void orderedAdd(T* obj);
  void orderedInsert(uint list_num, T* obj);
  void balance();
  void resize(uint new_size);
  void loadFromBin(fstream &in);
  void loadToBin(fstream &out);
  template<class V>
  friend istream &operator>>(istream &is, TLList<V> &tl_list);
  template<class V>
  friend ostream &operator<<(ostream &os, TLList<V> &tl_list);
  private:
  void swap(uint l, uint p);
  elem<T>* getItem(uint l, uint p);
  node<T>* getNode(uint l);
  uint capacity_;
  uint size_;
  node<T>* node_head_;
};

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
      node<V>* n_tmp = tl_list.node_head_;
      while (n_tmp) {
        elem<V>* e_tmp = n_tmp->head;
        while (e_tmp) {
          os << *(e_tmp->obj) << " ";
          e_tmp = e_tmp->next;
        }
        n_tmp = n_tmp->next;
        if (n_tmp)
          os << "\n";
      }
      return os;
    }
