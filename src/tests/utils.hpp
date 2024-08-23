#pragma once
#include <cstdint>
#include <iostream>
#include "../tetris.hpp"

#if defined(__GNUC__) || defined(__clang__)
#define RESTRICT __restrict__
#elif defined(_MSC_VER)
#define RESTRICT __restrict
#else
#define RESTRICT
#endif

void print_board(const Board board) {
  puts("+--------------------+");
  for(int i = 20; i--;) {
    putchar_unlocked('|');
    for(int j = 0; j < 10; ++j) {
      printf(get(board, j, i) ? "[]" : "  ");
    }
    putchar_unlocked('|');
    putchar_unlocked('\n');
  }
  puts("+--------------------+");
}

void assertLinesCleared(int linesCleared, int expected) {
  if (linesCleared != expected) {
    std::cerr << "Clearing full board should clear " << expected
              << " lines, actually cleared " << linesCleared << " lines"
              << std::endl;
    abort();
  }
}

void assertBoardsEqual(const Board RESTRICT left, const Board RESTRICT right) {
  for(int i = 10; i--;) {
    if(left[i] != right[i]) {
      std::cerr << "Assertion failed: boards not equal\n";
      std::cerr << "Left:                  Right:\n";
      std::cerr << "+--------------------+ +--------------------+\n";
      for(int i = 20; i--;) {
        std::cerr << '|';
        for(int j = 0; j < 10; ++j) {
          std::cerr << get(left, j, i) ? "[]" : "  ";
        }
        std::cerr << "| |";
        for(int j = 0; j < 10; ++j) {
          std::cerr << get(right, j, i) ? "[]" : "  ";
        }
        std::cerr << "|\n";
      }
      std::cerr << "+--------------------+ +--------------------+" << std::endl;
      abort();
    }
  }
}

// void assertBoardsEqual(Board const &left, Board const &right) {
//   bool equal = true;
//   for (int row = 0; row < 20 && equal; row++) {
//     for (int col = 0; col < 10; col++) {
//       if (left[row][col] != right[row][col]) {
//         equal = false;
//         break;
//       }
//     }
//   }
//   if (!equal) {
//     std::cerr << "Assertion failed: boards not equal" << std::endl;
//     std::cerr << "Left:     \tRight:" << std::endl;
//     for (int row = 0; row < 20; row++) {
//       for (int col = 0; col < 10; col++) {
//         if (left[row][col] != right[row][col]) {
//           std::cerr << "\033[1;31m";
//         }
//         std::cerr << unsigned(left[row][col]);
//         std::cerr << "\033[0m";
//       }
//       std::cerr << "\t";
//       for (int col = 0; col < 10; col++) {
//         if (left[row][col] != right[row][col]) {
//           std::cerr << "\033[1;31m";
//         }
//         std::cerr << unsigned(right[row][col]);
//         std::cerr << "\033[0m";
//       }
//       std::cerr << std::endl;
//     }
//     abort();
//   }
// }
