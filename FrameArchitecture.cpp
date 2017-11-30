#include "FrameArchitecture.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <vector>
bool FrameArchitecture::generated = false;
std::vector<std::vector<int>> FrameArchitecture::sequences =
    std::vector<std::vector<int>>(101, std::vector<int>(1000));
std::vector<std::vector<int>> FrameArchitecture::results =
    std::vector<std::vector<int>>(101, std::vector<int>(101, 0));
int FrameArchitecture::anamolies = 0;
void FrameArchitecture::generateSequences() {
  for (auto &row : sequences) {
    std::generate(row.begin(), row.end(), []() { return (std::rand() % 250); });
  }
};

void FrameArchitecture::printResults() {
  for (size_t i = 0; i < results.size(); i++) {
    for (size_t k = 0; k < results[i].size(); k++) {
      std::cout << results[i][k] << ",";
    }
    std::cout << std::endl;
  }
};
void FrameArchitecture::printSequences() {
  for (auto &row : sequences) {
    for (auto &i : row) {
      std::cout << i << ", ";
    }
    std::cout << std::endl;
  }
};
void FrameArchitecture::checkForAnamoly() {
  int min = 10000;
  int frame, sequence;
  size_t i, j = 0;
  std::cout << "Length of memory reference string: " << sequences[0].size()
            << std::endl;
  std::cout << "Frames of physical memory: " << sequences.size() - 1
            << std::endl
            << std::endl;
  for (i = 1; i < results.size(); i++) {
    for (j = 2; j < results[i].size(); j++) {
      // if (results[j][i] > results[j - 1][i]) {
      //   anamolies++;
      //
      //   std::cout << "Anamoly Discovered! " << std::endl;
      //   std::cout << "\t Sequence: " << i << " " << std::endl;
      //   std::cout << "\t Page Faults: " << results[j - 1][i]
      //             << " Frame size: " << j - 1 << std::endl;
      //
      //   std::cout << "\t Page Faults: " << results[j][i] << " Frame size: "
      //   << j
      //             << std::endl;
      // }

      if (results[j][i] <= min) {
        frame = j;
        sequence = i;
        min = results[j][i];
      } else {
        anamolies++;

        std::cout << "Anamoly Discovered! " << std::endl
                  << "\t Sequence: " << sequence << " " << std::endl
                  << "\t Page Faults: " << results[frame][i]
                  << " @ Frame Size: " << frame << std::endl
                  << "\t Page Faults: " << results[j][i]
                  << " @ Frame Size: " << j << std::endl;
      }
    }
    min = 10000;
  }
  std::cout << std::endl
            << std::endl
            << "Anamoly detected " << anamolies << " times." << std::endl;
};

void FrameArchitecture::simulate() {
  pageFaults = 0;
  for (int i = 1; i < sequences.size(); i++) {
    for (int j = 0; j < 1000; j++) {
      if (!inQueue[sequences[i][j]]) {
        if (pages.size() < frames) {
          pages.push(sequences[i][j]);
          inQueue[sequences[i][j]] = true;
          pageFaults++;
        } else {
          inQueue[pages.front()] = false;
          pages.pop();
          pages.push(sequences[i][j]);
          inQueue[sequences[i][j]] = true;
          pageFaults++;
        }
      }
    }
    results[frames][i] = pageFaults;
    pageFaults = 0;
    for (int k = 0; k != pages.size();) {
      inQueue[pages.front()] = false;
      pages.pop();
    }
  }
};

FrameArchitecture::FrameArchitecture(int frameSize) {

  frames = frameSize;
  if (!generated) {
    generated = true;
    generateSequences();
  }
};
