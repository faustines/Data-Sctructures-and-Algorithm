#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "llrb_multimap.h"

// Tester
int main() {
    LLRB_multimap<int,std::string> multimap;

    multimap.Insert(2, "apple");
    multimap.Insert(2, "green");
    multimap.Insert(7, "dog");
    multimap.Insert(7, "frog");
    multimap.Insert(8, "banana");
    multimap.Insert(16, "cat");
    multimap.Print();

    multimap.Remove(8);
    multimap.Print();
    multimap.Remove(2);
    multimap.Print();

    std::cout << "value of 7 is " << multimap.Get(7) << std::endl;
    std::cout << "value of 16 is " << multimap.Get(16) << std::endl;

    try {
        multimap.Get(17);
    } catch (std::exception &e) {
        std::cout << "Expected exception: " << e.what() << std::endl;
    }
    return 0;
}
