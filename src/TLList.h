#pragma once
#include <iostream>

using namespace std;

//TLLIST for TwoLevelledList
//TODO balancing;
//TODO deelting unused lists after compression
//TODO copy constructor
//TODO sorted insert
//TODO resize
//TODO operators
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
    uint size_;
    node(T* o);
    node();
    ~node();
};

template <class T>
class TLList {
    public:
        TLList();
        TLList(T* obj);
        TLList(TLList<T> &obj);
        ~TLList();
        T* getCurr();
        uint getSize();
        uint getCurrListSize();
        void begin();
        void nextList();
        void nextElem();
        void add(T* obj);
        void addList();
        void insertList(uint pos);
        void removeList(uint pos);
        void remove(uint list_num, uint elem_pos);
        void insert(uint list_num, uint elem_pos, T* obj);
        void sortLists();
        void balance();
        void compress();
        template <class V>
        friend istream& operator >> (istream& is, TLList<V>& tl_list);
        template <class V>
        friend ostream& operator << (ostream& os, TLList<V>& tl_list);
    private:
        void swap(uint l, uint p);
        elem<T>* getItem(uint l, uint p);
        node<T>* getNode(uint l);
        uint capacity_;
        uint size_;
        node<T>* node_head_;
        node<T>* curr_n_;
        elem<T>* curr_e_;
};

#include "TLList.inl"
