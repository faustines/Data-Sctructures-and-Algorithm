#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "llrb_map.h"

// Tester
int main() {
    LLRB_map<int,std::string> map;

    map.Insert(2, "apple");
    map.Insert(8, "banana");
    map.Insert(11, "dog");
    map.Insert(16, "cat");
    map.Print();
    
    map.Remove(8);
    map.Print();

    std::cout << "value of 16 is " << map.Get(16) << std::endl;

    try {
        map.Insert(16, "egg");
    } catch (std::exception &e) {
        std::cout << "Expected exception: " << e.what() << std::endl;
    }
    try {
        map.Get(17);
    } catch (std::exception &e) {
        std::cout << "Expected exception: " << e.what() << std::endl;
    }
    return 0;
}
