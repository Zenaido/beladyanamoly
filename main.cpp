#include "Memory.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main(int argc, char const *argv[]) {

  for (size_t i = 1; i < 101; i++) {
    Memory s = Memory(i);
    s.simulate();
  }

  Memory::checkForAnamoly();

  return 0;
};
