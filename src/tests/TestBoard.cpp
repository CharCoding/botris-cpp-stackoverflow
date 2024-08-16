#pragma once
#undef NDEBUG  // if removed, assert does nothing
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>

#include "../tetris.hpp"

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

void clearFullBoard() {
  Board b = {{0}};
  for (int i = 0; i < 20; i++) {
    std::fill_n(b[i], 10, 1);
  }
  Board const empty = {{0}};
  uint8_t t = 0;
  int linesCleared = clear_lines(b);
  assertLinesCleared(linesCleared, 20);
  assertBoardsEqual(b, empty);
}

void clearOneLine() {
  Board b = {{0}};
  Board const expected = {{0}};
  for (int targetRow = 0; targetRow < 20; targetRow++) {
    std::fill_n(b[targetRow], 10, 1);
    int linesCleared = clear_lines(b);
    assertLinesCleared(linesCleared, 1);
    assertBoardsEqual(b, expected);
  }
}

void clearDisjointedLines() {
  Board b = {{0}};
  Board expected = {{0}};
  std::fill_n(b[0], 10, 1);
  std::fill_n(b[19], 10, 1);
  int linesCleared = clear_lines(b);
  assertLinesCleared(linesCleared, 2);
  assertBoardsEqual(b, expected);
  std::fill_n(b[10], 10, 1);
  std::fill_n(b[12], 10, 1);
  b[9][0] = expected[9][0] = 1;
  b[9][1] = expected[9][1] = 1;
  b[11][1] = expected[10][1] = 1;
  b[11][2] = expected[10][2] = 1;
  b[13][2] = expected[11][2] = 1;
  b[13][3] = expected[11][3] = 1;
  linesCleared = clear_lines(b);
  assertLinesCleared(linesCleared, 2);
  assertBoardsEqual(b, expected);
}

void dontClearAlmostFullLines() {
  Board b = {
      {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 0
      {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 1
      {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},  // 2
      {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},  // 3
      {1, 1, 0, 1, 1, 1, 1, 1, 1, 1},  // 4
      {1, 1, 0, 1, 1, 1, 1, 1, 1, 1},  // 5
      {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},  // 6
      {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},  // 7
      {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},  // 8
      {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},  // 9
      {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},  // 10
      {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},  // 11
      {1, 1, 1, 1, 1, 1, 0, 1, 1, 1},  // 12
      {1, 1, 1, 1, 1, 1, 0, 1, 1, 1},  // 13
      {1, 1, 1, 1, 1, 1, 1, 0, 1, 1},  // 14
      {1, 1, 1, 1, 1, 1, 1, 0, 1, 1},  // 15
      {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},  // 16
      {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},  // 17
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 18
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 19
  };
  Board expected;
  std::copy(&b[0][0], &b[0][0] + 20 * 10, &expected[0][0]);

  int linesCleared = clear_lines(b);
  assertLinesCleared(linesCleared, 0);
  assertBoardsEqual(b, expected);
}

void hachispin() {
  Board first = {
      {1, 1, 0, 0, 0, 1, 1, 1, 1, 0},  // 0
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 1
      {1, 0, 1, 1, 1, 1, 1, 1, 1, 0},  // 2
      {1, 0, 0, 0, 0, 1, 1, 0, 0, 0},  // 3
      {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},  // 4
  };
  Board first_expected = {
      {1, 1, 0, 0, 0, 1, 1, 1, 1, 0},  // 0
      {1, 0, 1, 1, 1, 1, 1, 1, 1, 0},  // 1
      {1, 0, 0, 0, 0, 1, 1, 0, 0, 0},  // 2
      {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},  // 3
  };
  int linesCleared = clear_lines(first);
  assertLinesCleared(linesCleared, 1);
  assertBoardsEqual(first, first_expected);
  Board second = {
      {1, 1, 0, 0, 0, 1, 1, 1, 1, 1},  // 0
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 1
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 2
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 3
      {1, 0, 0, 0, 0, 1, 1, 1, 1, 1},  // 4
      {1, 1, 0, 0, 0, 0, 0, 1, 0, 0},  // 5
  };
  Board second_expected = {
      {1, 1, 0, 0, 0, 1, 1, 1, 1, 1},  // 0
      {1, 0, 0, 0, 0, 1, 1, 1, 1, 1},  // 1
      {1, 1, 0, 0, 0, 0, 0, 1, 0, 0},  // 2
  };
  linesCleared = clear_lines(second);
  assertLinesCleared(linesCleared, 3);
  assertBoardsEqual(second, second_expected);
  Board pc_half = {
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 0
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 1
      {1, 1, 0, 0, 1, 0, 0, 1, 0, 0},  // 2
  };
  Board pc_half_expected = {
      {1, 1, 0, 0, 1, 0, 0, 1, 0, 0},  // 0
  };
  linesCleared = clear_lines(pc_half);
  assertLinesCleared(linesCleared, 2);
  assertBoardsEqual(pc_half, pc_half_expected);
  Board pc = {
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 0
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 1
  };
  Board pc_expected = {{0}};
  linesCleared = clear_lines(pc);
  assertLinesCleared(linesCleared, 2);
  assertBoardsEqual(pc, pc_expected);
}

int main() {
  clearFullBoard();
  clearOneLine();
  clearDisjointedLines();
  dontClearAlmostFullLines();
  hachispin();
  return 0;
}