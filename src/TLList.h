#pragma once
#include <iostream>

using namespace std;

//TLLIST for TwoLevelledList
//Todo add, insert, remove
//TODO googletest
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
    int size_;
    node(T* o);
    ~node();
};

template <class T>
class TLList {
    public:
        TLList();
        TLList(T* obj);
        ~TLList();
    void add(T* obj);
    void resize(int newsize);
    template <class V>
        friend istream& operator >> (istream& is, TLList<V>& tl_list);
        template <class V>
        friend ostream& operator << (ostream& os, TLList<V>& tl_list);
    private:
        int capacity_;
        node<T>* head_;
        node<T>* curr_n_;
        elem<T>* curr_e_;
};

#include "TLList.inl"
