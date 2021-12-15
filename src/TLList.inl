#pragma once
#include "TLList.h"

template <class T>
node<T>::node(T* o) {
    head = new elem<T>(o);
    next = nullptr;
    size_ = 1;
}

template <class T>
node<T>::~node() {
    while (head != nullptr) {
        elem<T>* tmp = head;
        head = head->next;
        delete tmp;
    }
}

template<typename T>
TLList<T>::TLList() {
    head_ = nullptr;
    curr_n_ = nullptr;
    curr_e_ = nullptr;
    capacity_ = 10;
}

template<typename T>
TLList<T>::TLList(T *object_ptr_) {
    head_ = new node<T>(object_ptr_);
    curr_n_ = head_;
    curr_e_ = curr_n_->head;
    capacity_ = 10;
}

template<typename T>
TLList<T>::~TLList() {
    curr_n_ = head_;
    while (curr_n_ != nullptr) {
        node<T>* ntmp = curr_n_;
        curr_n_ = curr_n_->next;
        delete ntmp;
    }
}

template<class V>
istream &operator >> (istream &is, TLList<V>& tl_list) {
    return is;
}

template<class V>
ostream &operator<<(ostream &os, TLList<V> &tl_list) {
    node<V>* ntmp = tl_list.head_;
    while (ntmp != nullptr) {
        elem<V>* etmp = ntmp->head;
        while (etmp != nullptr) {
            os << *(etmp->obj) << " ";
            etmp = etmp->next;
        }
        ntmp = ntmp->next;
    }
    return os;
}

template<class T>
void TLList<T>::add(T* obj) {
    if (!head_) {
        head_ = new node<T>(obj);
    } else {
        node<T>* ntmp = head_;
        while (ntmp->size_ >= capacity_ && !(ntmp->next)) ntmp = ntmp->next;
        if (ntmp->size_ < capacity_) {
            ntmp->size_++;
            elem<T>* etmp = ntmp->head;
            while(etmp->next) etmp = etmp->next;
            etmp->next = new elem<T>(obj);
        } else {
            ntmp->next = new node<T>(obj);
        }
    }
}
template<class T>
void TLList<T>::resize(int newsize) {

}
