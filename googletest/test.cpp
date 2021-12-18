#include "gtest/gtest.h"
#include <iostream>
#include <sstream>
#include <string>
#include "../src/TLList.h"

TEST(LIST, creating) {
    int* a = new int;
    int* b = new int;
    int* c = new int;
    int* d = new int;
    *a = 5; *b = 2; *c = -8; *d = -13;
    TLList<int> l1;
    l1.add(a);
    l1.add(b);
    l1.add(c);
    ASSERT_EQ(*(l1.getCurr()), *a);
    l1.nextList();
    ASSERT_EQ(*(l1.getCurr()), *a);
    l1.nextElem();
    ASSERT_EQ(*(l1.getCurr()), *b);
    l1.nextElem();
    ASSERT_EQ(*(l1.getCurr()), *c);
    l1.nextElem();
    ASSERT_EQ(*(l1.getCurr()), *c);
    l1.insert(0, 1, d);
    ASSERT_EQ(*(l1.getCurr()), *c);
    ASSERT_EQ(l1.getCurrListSize(), 4);
    delete a; delete b; delete c; delete d;
}

TEST(LIST, insert_and_remove) {
    int* a = new int(2);
    int* b = new int(0);
    int* c = new int(-7);
    int* d = new int(23);
    int* e = new int(9);
    int* f = new int(5);
    int* g = new int(12);
    TLList<int> l2(a);
    l2.add(b);
    l2.add(c);
    ASSERT_EQ(*(l2.getCurr()), 2);
    l2.nextElem();
    ASSERT_EQ(*(l2.getCurr()), 0);
    l2.nextElem();
    ASSERT_EQ(*(l2.getCurr()), -7);
    l2.remove(0, 0);
    l2.begin();
    ASSERT_EQ(*(l2.getCurr()), 0);
    ASSERT_ANY_THROW(l2.insert(0, 5, f));
    l2.insertList(0);
    ASSERT_ANY_THROW(l2.insert(0, 1, g));
    l2.insert(0, 0, d);
    l2.begin();
    ASSERT_EQ(*(l2.getCurr()), 23);
    l2.addList();
    l2.insert(2, 0, e);
    l2.nextList(); l2.nextList();
    ASSERT_EQ(*(l2.getCurr()), 9);
    delete a; delete b; delete c; delete d; delete e; delete f; delete g;
}

TEST(LIST, sort) {
    int* a = new int(1);
    int* b = new int(4);
    int* c = new int(3);
    int* d = new int(8);
    int* e = new int(-9);
    int* f = new int(5);
    TLList<int> l3;
    l3.add(a);
    l3.add(b);
    l3.add(c);
    l3.addList();
    l3.insert(1, 0, d);
    l3.insert(1, 1, e);
    l3.insert(1, 2, f);
    l3.sortLists();
    std::cout << l3;
    delete a; delete b; delete c; delete d; delete e; delete f;
}

TEST(LIST, compress) {
    int* a = new int(1);
    int* b = new int(4);
    int* c = new int(3);
    int* d = new int(8);
    int* e = new int(-9);
    int* f = new int(5);
    int* g = new int(12);
    TLList<int> l3;
    l3.add(a);
    l3.add(b);
    l3.add(c);
    l3.addList();
    l3.insert(1, 0, d);
    l3.insert(1, 1, e);
    l3.insert(1, 2, f);
    l3.insert(1, 3, g);
    std::cout << l3;
    l3.compress();
    l3.sortLists();
    std::cout << l3;
    delete a; delete b; delete c; delete d; delete e; delete f; delete g;
}

TEST(LIST, copy_cons) {
    int* a = new int(1);
    int* b = new int(4);
    int* c = new int(3);
    int* d = new int(8);
    int* e = new int(-9);
    int* f = new int(5);
    int* g = new int(12);
    TLList<int> l3;
    l3.add(a);
    l3.add(b);
    l3.add(c);
    l3.addList();
    l3.addList();
    l3.insert(2, 0, d);
    l3.insert(2, 1, e);
    l3.insert(2, 2, f);
    l3.insert(2, 2, g);
    TLList<int> l4(l3);
    std::cout << l3;
    std::cout << l4;
    delete a; delete b; delete c; delete d; delete e; delete f; delete g;
}

TEST(LIST, operators) {
    TLList<int> l5;
    TLList<char> l6;
    TLList<string> l7;
    std::stringstream ss;
    ss << "22 qwerty aboba";
    ss >> l5 >> l6 >> l7 >> l7;
    std::cout << l5 << l6 << l7;
}

TEST (LIST, binary) {
    int* a = new int(1);
    int* b = new int(4);
    int* c = new int(3);
    int* d = new int(8);
    int* e = new int(-9);
    int* f = new int(5);
    int* g = new int(12);
    TLList<int> l3;
    l3.add(a);
    l3.add(b);
    l3.add(c);
    l3.addList();
    l3.addList();
    l3.insert(2, 0, d);
    l3.insert(2, 1, e);
    l3.insert(2, 2, f);
    l3.insert(2, 2, g);
    std::ofstream binout;
    binout.open("../../googletest/test.bin", ios::binary| ios::out);
    l3.loadToBin(binout);
    binout.close();
    std::ifstream binin;
    binin.open("../../googletest/test.bin", ios::binary| ios::in);
    l3.loadFromBin(binin);
    std::cout << l3 << "\n";
    binin.close();
    l3.compress();
    l3.sortLists();
    std::cout << "-\n" << l3 << "----\n";
    delete a; delete b; delete c; delete d; delete e; delete f; delete g;
}
