#include "FrameArchitecture.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main(int argc, char const *argv[]) {

  for (size_t i = 1; i < 101; i++) {
    FrameArchitecture s = FrameArchitecture(i);
    s.simulate();
  }

  FrameArchitecture::checkForAnamoly();

  return 0;
};
