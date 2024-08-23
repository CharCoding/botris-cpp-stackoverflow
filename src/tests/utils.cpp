#pragma once
#include <cstdint>
#include <iostream>

using Board = uint8_t[20][10];

void displayBoard(Board const &b) {
  for (int row = 0; row < 20; row++) {
    for (int col = 0; col < 10; col++) {
      // without unsigned, tries to print char with ascii value, which is
      // usually invisible
      std::cout << unsigned(b[row][col]);
    }
    std::cout << std::endl;
  }
}

void assertLinesCleared(int linesCleared, int expected) {
  if (linesCleared != expected) {
    std::cerr << "Clearing full board should clear " << expected
              << " lines, actually cleared " << linesCleared << " lines"
              << std::endl;
    abort();
  }
}

void assertBoardsEqual(Board const &left, Board const &right) {
  bool equal = true;
  for (int row = 0; row < 20 && equal; row++) {
    for (int col = 0; col < 10; col++) {
      if (left[row][col] != right[row][col]) {
        equal = false;
        break;
      }
    }
  }
  if (!equal) {
    std::cerr << "Assertion failed: boards not equal" << std::endl;
    std::cerr << "Left:     \tRight:" << std::endl;
    for (int row = 0; row < 20; row++) {
      for (int col = 0; col < 10; col++) {
        if (left[row][col] != right[row][col]) {
          std::cerr << "\033[1;31m";
        }
        std::cerr << unsigned(left[row][col]);
        std::cerr << "\033[0m";
      }
      std::cerr << "\t";
      for (int col = 0; col < 10; col++) {
        if (left[row][col] != right[row][col]) {
          std::cerr << "\033[1;31m";
        }
        std::cerr << unsigned(right[row][col]);
        std::cerr << "\033[0m";
      }
      std::cerr << std::endl;
    }
    abort();
  }
}
