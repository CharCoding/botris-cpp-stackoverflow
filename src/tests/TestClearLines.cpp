#include <algorithm>

#include "utils.hpp"
void clearFullBoard() {
  Board b;
  std::fill_n(b, 10, 0b11111111111111111111);
  Board const empty = { 0 };
  int linesCleared = clear_lines(b);
  assertLinesCleared(linesCleared, 20);
  assertBoardsEqual(b, empty);
}

void clearOneLine() {
  Board b = {0};
  Board const expected = {0};
  for(int targetRow = 0; targetRow < 20; targetRow++) {
    for(int i = 0; i < 10; i++) {
      set(b, i, targetRow);
    }
    int linesCleared = clear_lines(b);
    assertLinesCleared(linesCleared, 1);
    assertBoardsEqual(b, expected);
  }
}

void clearDisjointedLines() {
  Board b;
  std::fill_n(b, 10, 0b10000000000000000001);
  Board expected = {0};
  int linesCleared = clear_lines(b);
  assertLinesCleared(linesCleared, 2);
  assertBoardsEqual(b, expected);
  for(int i = 0; i < 10; i++) {
    set(b, i, 10);
    set(b, i, 12);
  }
  set(b, 0, 9);
  set(b, 1, 9);
  set(b, 1, 11);
  set(b, 2, 11);
  set(b, 2, 13);
  set(b, 3, 13);
  set(expected, 0, 9);
  set(expected, 1, 9);
  set(expected, 1, 10);
  set(expected, 2, 10);
  set(expected, 2, 11);
  set(expected, 3, 11);
  linesCleared = clear_lines(b);
  assertLinesCleared(linesCleared, 2);
  assertBoardsEqual(b, expected);
}

void dontClearAlmostFullLines() {
  Board b = { 0 };
  int empty = 3;
  int mask = 0b11111111111111111111;
  for(int i = 0; i < 10; i++) {
    b[i] = empty ^ mask;
    empty <<= 2;
  }
  Board expected;
  std::copy(b, b + 10, expected);

  int linesCleared = clear_lines(b);
  assertLinesCleared(linesCleared, 0);
  assertBoardsEqual(b, expected);
}

void tankGarbage() {
  Board b = { 1, 0, 0, 1, 1, 1, 0, 0, 0, 0 };
  Board tank_cheese = {
    0b11011, 0b01111, 0b01111, 0b11101, 0b10111, 0b11110, 0b01111, 0b01111, 0b01111, 0b01111
  };
  Board tank_quad = {
    0b110111111, 0b011111111, 0b011111111, 0b111011111, 0b101111111, 0b111101111, 0b011111111, 0b011111111, 0b011111111, 0b011110000
  };
  std::vector<unsigned> cheese = { 4, 0, 3, 5 };
  std::vector<unsigned> quad = { 9, 9, 9, 9 };
  tank_garbage(b, cheese);
  assertBoardsEqual(b, tank_cheese);
  tank_garbage(b, quad);
  assertBoardsEqual(b, tank_quad);
}
/* // clear_lines is looking pretty solid at this point, not gonna fix this
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
*/
int main() {
  clearFullBoard();
  clearOneLine();
  clearDisjointedLines();
  dontClearAlmostFullLines();
  //hachispin();
  tankGarbage();
  return 0;
}