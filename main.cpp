#include <iostream>
#include "src/TLList.h"

int main() {
    int* a = new int;
    int* b = new int;
    int* c = new int;
    *a = 5; *b = 2; *c = -8;
    TLList<int> aboba;
    std::cout << aboba;
    aboba.add(a);
    std::cout << aboba;
    aboba.add(b);
    std::cout << aboba;
    aboba.add(c);
    std::cout << aboba;
}
