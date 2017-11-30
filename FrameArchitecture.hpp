#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
#include <queue>
#include <vector>
class FrameArchitecture {
private:
  static std::vector<std::vector<int>> results;
  static std::vector<std::vector<int>> sequences;
  std::vector<bool> inQueue = std::vector<bool>(250, false);
  static bool generated;
  static int anamolies;
  int frames;
  int pageFaults = 0;
  std::queue<int> pages;

  void generateSequences();

public:
  static void printResults();
  void simulate();
  static void checkForAnamoly();

  bool checkVector();
  static void printSequences();
  void printInQueue() {
    for (size_t i = 0; i < inQueue.size(); i++) {
      std::cout << inQueue[i] << ',';
    }
  }
  FrameArchitecture(int frameSize);
};
#endif
