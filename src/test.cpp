#include <cstdio>

#include "tetris.hpp"

void print_board(const Board& board) {
  puts("+--------------------+");
  for(int i = 20; i--;) {
    putchar_unlocked('|');
    for(int j = 0; j < 10; ++j) {
      printf(board[i][j] ? "[]" : "  ");
    }
    putchar_unlocked('|');
    putchar_unlocked('\n');
  }
  puts("+--------------------+");
}

// note y is subtracted from coordinate due to y increase downward in the terminal, and x is doubled to print []
void print_piece(Piece p, Rotation r, int row, int col) {
  // piece[p][r] is the rotation center; I and O pieces should work the same
  //                                   Y                       X
  printf("\033[%d;%dH[]", col - pieces[p][r    ], row + pieces[p][r    ] * 2);
  printf("\033[%d;%dH[]", col - pieces[p][r + 2], row + pieces[p][r + 1] * 2);
  printf("\033[%d;%dH[]", col - pieces[p][r + 4], row + pieces[p][r + 3] * 2);
  printf("\033[%d;%dH[]", col - pieces[p][r + 6], row + pieces[p][r + 5] * 2);
}
int main() {
  int x = 4, y = 4;
  for (int r = 0; r < 32; r += 8) {
    for (int i = 0; i < 7; ++i) {
      print_piece(Piece(i), Rotation(r), x, y);
      x += 10;
    }
    x = 4;
    y += 5;
  }
  putchar_unlocked('\n');
  Board board = { // note it's upside down
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
  };
  print_board(board);
  clear_lines(board);
  print_board(board);
}