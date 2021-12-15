#pragma once
#include <iostream>

using namespace std;

//TLLIST for TwoLevelledList
//TODO resize
//TODO lib
//TODO operators
//TODO sort, sorted insert balancing
//TODO saving and loading from bin
//TODO interacting with strings
//TODO menu

template <class T>
struct elem {
    T* obj;
    struct elem* next;
    elem(T* o) { obj = o; next = nullptr; }
    ~elem() { delete obj; }
};

template <class T>
struct node {
    elem<T>* head;
    struct node* next;
    unsigned int size_;
    node(T* o);
    node();
    ~node();
};

template <class T>
class TLList {
    public:
        TLList();
        TLList(T* obj);
        ~TLList();
        T* getCurr();
        unsigned int getSize();
        unsigned int getCurrListSize();
        void begin();
        void nextList();
        void nextElem();
        void add(T* obj);
        void addList();
        void insertList(unsigned int pos);
        void removeList(unsigned int pos);
        void remove(unsigned int list_num, unsigned int elem_pos);
        void insert(unsigned int list_num, unsigned int elem_pos, T* obj);
        template <class V>
        friend istream& operator >> (istream& is, TLList<V>& tl_list);
        template <class V>
        friend ostream& operator << (ostream& os, TLList<V>& tl_list);
    private:
        unsigned int capacity_;
        unsigned int size_;
        node<T>* node_head_;
        node<T>* curr_n_;
        elem<T>* curr_e_;
};

#include "TLList.inl"
