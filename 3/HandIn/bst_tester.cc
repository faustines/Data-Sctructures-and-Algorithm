#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "bst.h"

int main() {
  std::vector<int> keys{51, 43, 93, 18, 42, 99, 54, 2, 74};

  BST<int> bst;

  try {
    bst.ceil(42);
  } catch (std::exception &e) {
    std::cout << "Expected exception: " << e.what() << std::endl;
  }
  try {
    bst.floor(42);
  } catch (std::exception &e) {
    std::cout << "Expected exception: " << e.what() << std::endl;
  }
  try {
    bst.kth_small(42);
  } catch (std::exception &e) {
    std::cout << "Expected exception: " << e.what() << std::endl;
  }

  for (auto i : keys)
    bst.insert(i);

  /* Test ceil */
  std::cout << "ceil(54) = " << bst.ceil(54) << "\n";
  std::cout << "ceil(55) = " << bst.ceil(55) << "\n";
  std::cout << "ceil(98) = " << bst.ceil(98) << "\n";
  std::cout << "ceil(1) = " << bst.ceil(1) << "\n";

  try {
    bst.ceil(100);
  } catch (std::exception &e) {
    std::cout << "Expected exception: " << e.what() << std::endl;
  }


  /* Test floor */
  std::cout << "floor(54) = " << bst.floor(54) << "\n";
  std::cout << "floor(55) = " << bst.floor(55) << "\n";
  std::cout << "floor(100) = " << bst.floor(100) << "\n";
  std::cout << "floor(3) = " << bst.floor(3) << "\n";

  try {
    bst.floor(-100);
  } catch (std::exception &e) {
    std::cout << "Expected exception: " << e.what() << std::endl;
  }


  /* Test kth_small */
  std::cout << "kth(1) = " << bst.kth_small(1) << "\n";
   std::cout << "kth(5) = " << bst.kth_small(5) << "\n";

   try {
     bst.kth_small(100);
   } catch (std::exception &e) {
     std::cout << "Expected exception: " << e.what() << std::endl;
   }
   try {
     bst.kth_small(-100);
   } catch (std::exception &e) {
     std::cout << "Expected exception: " << e.what() << std::endl;
   }
   try {
     bst.kth_small(0);
   } catch (std::exception &e) {
     std::cout << "Expected exception: " << e.what() << std::endl;
   }

  return 0;
}
