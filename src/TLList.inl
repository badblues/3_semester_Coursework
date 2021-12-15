#pragma once
#include "TLList.h"
#include <exception>

template <class T>
node<T>::node(T* o) {
    head = new elem<T>(o);
    next = nullptr;
    size_ = 1;
}

template <class T>
node<T>::node() {
    head = nullptr;
    next = nullptr;
    size_ = 0;
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
    size_ = 0;
    node_head_ = nullptr;
    curr_n_ = nullptr;
    curr_e_ = nullptr;
    capacity_ = 10;
}

template<typename T>
TLList<T>::TLList(T *object_ptr_) {
    size_ = 1;
    node_head_ = new node<T>(object_ptr_);
    curr_n_ = node_head_;
    curr_e_ = curr_n_->head;
    capacity_ = 10;
}

template<typename T>
TLList<T>::~TLList() {
    curr_n_ = node_head_;
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
    node<V>* ntmp = tl_list.node_head_;
    while (ntmp != nullptr) {
        elem<V>* etmp = ntmp->head;
        while (etmp != nullptr) {
            os << *(etmp->obj) << " ";
            etmp = etmp->next;
        }
        os << "\n";
        ntmp = ntmp->next;
    }
    return os;
}

template<class T>
T* TLList<T>::getCurr() {
    if (curr_e_)
        return curr_e_->obj;
    return {};
}

template<class T>
unsigned int TLList<T>::getSize() {
    return size_;
}

template<class T>
    unsigned int TLList<T>::getCurrListSize() {
    return curr_n_->size_;
}


template<class T>
void TLList<T>::begin() {
    curr_n_ = node_head_;
    if (curr_n_) {
        curr_e_ = curr_n_->head;
    }
}

template<class T>
void TLList<T>::nextList() {
    if (curr_n_ && curr_n_->next) {
        curr_n_ = curr_n_->next;
        curr_e_ = curr_n_->head;
    }
}

template<class T>
void TLList<T>::nextElem() {
    if (curr_e_ && curr_e_->next)
        curr_e_ = curr_e_->next;
}

template<class T>
void TLList<T>::add(T* obj) {
    size_++;
    if (!node_head_) {
        node_head_ = new node<T>(obj);
        curr_n_ = node_head_;
        curr_e_= curr_n_->head;
    } else {
        node<T>* ntmp = node_head_;
        while (ntmp->size_ >= capacity_ && ntmp->next) ntmp = ntmp->next;
        if (ntmp->size_ < capacity_) {
            elem<T>* etmp = ntmp->head;
            while(etmp->next) etmp = etmp->next;
            etmp->next = new elem<T>(obj);
            ntmp->size_++;
        } else {
            ntmp->next = new node<T>(obj);
        }
    }
}

template <class T>
void TLList<T>::addList() {
    if (!node_head_) {
        node_head_ = new node<T>;
    } else {
        node<T>* ntmp = node_head_;
        while(ntmp->next) ntmp = ntmp->next;
        ntmp->next = new node<T>;
    }
    size_++;
}

template <class T>
void TLList<T>::insertList(unsigned int pos) {
    if (pos > size_)
        throw out_of_range("N/A INDEX");
    if (pos == 0) {
        node<T>* ntmp = node_head_;
        node_head_ = new node<T>;
        node_head_->next = ntmp;
    } else {
        node<T>* ntmp = node_head_;
        for (unsigned int i = 0; i < pos - 1; i++) ntmp = ntmp->next;
        node<T>* ntmp2 = ntmp->next;
        ntmp->next = new node<T>;
        ntmp->next->next = ntmp2;
    }
    size_++;
}

template <class T>
void TLList<T>::removeList(unsigned int pos) {
    if (pos >= size_)
        throw out_of_range("N/A INDEX");
    if (pos == 0) {
        node<T>* ntmp = node_head_->next;
        delete node_head_;
        node_head_ = ntmp;
    } else {
        node<T>* ntmp = node_head_;
        for (unsigned int i = 0; i < pos - 1; i++) ntmp = ntmp->next;
        node<T>* ntmp2 = ntmp->next;
        ntmp->next = ntmp->next->next;
        delete ntmp2;
    }
    size_--;
}

template<class T>
void TLList<T>::remove(unsigned int list_num, unsigned int elem_pos) {
    if (list_num >= size_ || elem_pos >= capacity_)
        throw out_of_range("N/A INDEX");
    node<T>* ntmp = node_head_;
    for (unsigned int i = 0; i < list_num; i++) ntmp = ntmp->next;
    if (elem_pos >= ntmp->size_)
        throw out_of_range("N/A INDEX");
    if (elem_pos == 0) {
        elem<T>* etmp = ntmp->head;
        ntmp->head = ntmp->head->next;
        if (curr_e_ == etmp)
            curr_e_ = ntmp->head;
        delete etmp;
        size_--;
    } else {
        elem<T>* etmp = ntmp->head;
        for (unsigned int i = 0; i < elem_pos - 1; i++) etmp = etmp->next;
        elem<T>* etmp2 = etmp->next;
        etmp->next = etmp->next->next;
        if (curr_e_ == etmp2)
            curr_e_ = etmp->next;
        delete etmp2;
        size_--;
    }
}

template<class T>
void TLList<T>::insert(unsigned int list_num, unsigned int elem_pos, T* obj) {
    if (list_num >= size_ || elem_pos >= capacity_)
        throw out_of_range("N/A INDEX");
    node<T>* ntmp = node_head_;
    for (unsigned int i = 0; i < list_num; i++) ntmp = ntmp->next;
    if (elem_pos > ntmp->size_)
        throw out_of_range("N/A INDEX");
    if (ntmp->size_ == capacity_)
        throw overflow_error("ELEMENTS OVERFLOW");
    elem<T>* etmp2 = new elem<T>(obj);
    if (elem_pos == 0) {
        etmp2->next = ntmp->head;
        ntmp->head = etmp2;
    } else {
        elem<T>* etmp = ntmp->head;
        for (unsigned int i = 0; i < elem_pos - 1; i++) etmp = etmp->next;
        etmp2->next = etmp->next;
        etmp->next = etmp2;
    }
    ntmp->size_++;
}
