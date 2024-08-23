#include <cstdio>
#include <vector>

#include "../tetris.hpp"

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

// note y is subtracted from coordinate due to y increase downward in the terminal, and x is doubled to print []
void print_piece(Piece p, Rotation r, int row, int col) {
  //                                   Y                       X
  printf("\033[%d;%dH[]", col - piece_offsets[p][r][0].y, row + piece_offsets[p][r][0].x * 2);
  printf("\033[%d;%dH[]", col - piece_offsets[p][r][1].y, row + piece_offsets[p][r][1].x * 2);
  printf("\033[%d;%dH[]", col - piece_offsets[p][r][2].y, row + piece_offsets[p][r][2].x * 2);
  printf("\033[%d;%dH[]", col - piece_offsets[p][r][3].y, row + piece_offsets[p][r][3].x * 2);
}
int main() {
  int x = 4, y = 4;
  for (int r = 0; r < 4; ++r) {
    for (int i = 0; i < 7; ++i) {
      print_piece(Piece(i), Rotation(r), x, y);
      x += 10;
    }
    x = 4;
    y += 5;
  }
  puts("\033[21;0H");
  putchar_unlocked('\n');
  Board board = {
    0b001000111,
    0b001000111,
    0b001000111,
    0b001010111,
    0b001000111,
    0b011000111,
    0b011000111,
    0b001100111,
    0b001000111,
    0b001100110,
  };
  print_board(board);
  clear_lines(board);
  std::vector<unsigned> columns = {0, 3, 3, 6, 6, 6, 9, 9, 9, 9};
  tank_garbage(board, columns);
  print_board(board);
}