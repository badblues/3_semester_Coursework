#pragma once
#include <iostream>

using namespace std;
typedef unsigned int uint;

//TLLIST for TwoLevelledList
//TODO test: loading big strings, file interaction, menu
//TODO fix file loading

template<class T>
struct elem {
  T* obj;
  struct elem* next;
  elem(T* o) {
    obj = new T;
    *obj = *o;
    next = nullptr;
  }
  ~elem() { delete obj; }
};

template<class T>
struct node {
  elem<T>* head;
  struct node* next;
  uint size;
  node(T* o);
  node();
  ~node();
};

template<class T>
class TLList {
  public:
    TLList();
    explicit TLList(T* obj);
    TLList(TLList<T> &obj);
    ~TLList();
    T* getElem(uint list_num, uint elem_pos);
    uint getSize();
    uint getListSize(uint list_num);
    void add(T* obj);
    void addList();
    void insertList(uint pos);
    void removeList(uint pos);
    void remove(uint list_num, uint elem_pos);
    void insert(uint list_num, uint elem_pos, T* obj);
    void sortLists();
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

#include "TLList.inl"
