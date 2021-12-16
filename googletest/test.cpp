#include "gtest/gtest.h"
#include <iostream>
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
    ASSERT_EQ(l1.getCurr(), a);
    l1.nextList();
    ASSERT_EQ(l1.getCurr(), a);
    l1.nextElem();
    ASSERT_EQ(l1.getCurr(), b);
    l1.nextElem();
    ASSERT_EQ(l1.getCurr(), c);
    l1.nextElem();
    ASSERT_EQ(l1.getCurr(), c);
    l1.insert(0, 1, d);
    ASSERT_EQ(l1.getCurr(), c);
    ASSERT_EQ(l1.getCurrListSize(), 4);
}

TEST(LIST, insert_and_remove) {
    TLList<int> l2(new int(2));
    l2.add(new int(0));
    l2.add(new int(-7));
    ASSERT_EQ(*(l2.getCurr()), 2);
    l2.nextElem();
    ASSERT_EQ(*(l2.getCurr()), 0);
    l2.nextElem();
    ASSERT_EQ(*(l2.getCurr()), -7);
    l2.remove(0, 0);
    l2.begin();
    ASSERT_EQ(*(l2.getCurr()), 0);
    ASSERT_ANY_THROW(l2.insert(0, 5, new int(90)));
    l2.insertList(0);
    ASSERT_ANY_THROW(l2.insert(0, 1, new int(23)));
    l2.insert(0, 0, new int(23));
    l2.begin();
    ASSERT_EQ(*(l2.getCurr()), 23);
    l2.addList();
    l2.insert(2, 0, new int(9));
    l2.nextList(); l2.nextList();
    ASSERT_EQ(*(l2.getCurr()), 9);
}

TEST(LIST, sort) {
    TLList<int> l3;
    l3.add(new int(1));
    l3.add(new int(4));
    l3.add(new int(3));
    l3.addList();
    l3.insert(1, 0, new int(8));
    l3.insert(1, 1, new int(-9));
    l3.insert(1, 2, new int(5));
    l3.sortLists();
    std::cout << l3;
}

TEST(LIST, compress) {
    TLList<int> l3;
    l3.add(new int(1));
    l3.add(new int(4));
    l3.add(new int(3));
    l3.addList();
    l3.insert(1, 0, new int(8));
    l3.insert(1, 1, new int(-9));
    l3.insert(1, 2, new int(5));
    l3.insert(1, 2, new int(12));
    std::cout << l3;
    l3.compress();
    l3.sortLists();
    std::cout << l3;
}

TEST(LIST, copy_cons) {
    TLList<int> l3;
    l3.add(new int(1));
    l3.add(new int(4));
    l3.add(new int(3));
    l3.addList();
    l3.addList();
    l3.insert(2, 0, new int(8));
    l3.insert(2, 1, new int(-9));
    l3.insert(2, 2, new int(5));
    l3.insert(2, 2, new int(12));
    TLList<int> l4(l3);
    std::cout << l3;
    std::cout << l4;
}
