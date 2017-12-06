#include "Memory.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
bool Memory::generated = false;
std::vector<std::vector<int>> Memory::sequences =
    std::vector<std::vector<int>>(100, std::vector<int>(1000));
std::vector<std::vector<int>> Memory::results =
    std::vector<std::vector<int>>(100, std::vector<int>(100, 0));
int Memory::anamolies = 0;
void Memory::generateSequences() {
  for (auto &sequence : sequences) {
    std::generate(sequence.begin(), sequence.end(),
                  []() { return (std::rand() % 250); });
  }
}

void Memory::printResults() {
  for (size_t i = 0; i < results.size(); i++) {
    for (size_t k = 0; k < results[i].size(); k++) {
      std::cout << results[i][k] << ",";
    }
    std::cout << std::endl;
  }
}

void Memory::printSequences() {
  for (auto &sequence : sequences) {
    for (auto &i : sequence) {
      std::cout << i << ", ";
    }
    std::cout << std::endl;
  }
}

void Memory::checkForAnamoly() {
  int min = 10000;
  int frame, sequence;
  size_t i, j = 0;
  std::cout << "Length of memory reference string: " << sequences[0].size()
            << std::endl;
  std::cout << "Frames of physical memory: " << sequences.size() << std::endl
            << std::endl;

  for (i = 0; i < results.size(); i++) {
    for (j = 0; j < results[i].size(); j++) {

      if (results[j][i] <= min) {
        frame = j + 1;
        sequence = i;
        min = results[j][i];
      } else {
        anamolies++;

        std::cout << "Anamoly Discovered! " << std::endl
                  << "\t Sequence: " << sequence << " " << std::endl
                  << "\t Page Faults: " << results[frame][i]
                  << " @ Frame Size: " << frame << std::endl
                  << "\t Page Faults: " << results[j][i]
                  << " @ Frame Size: " << j + 1 << std::endl;
      }
    }
    min = 10000;
  }
  std::cout << std::endl
            << std::endl
            << "Anamoly detected " << anamolies << " times." << std::endl;
}

void Memory::simulate() {
  pageFaults = 0;
  for (int i = 0; i < sequences.size(); i++) {
    for (int j = 0; j < sequences[i].size(); j++) {
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
    results[frames - 1][i] = pageFaults;
    pageFaults = 0;
    for (int k = 0; k != pages.size();) {
      inQueue[pages.front()] = false;
      pages.pop();
    }
  }
}

Memory::Memory(int frameSize) {

  frames = frameSize;
  if (!generated) {
    generated = true;
    generateSequences();
  }
}
