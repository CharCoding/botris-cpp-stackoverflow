#include <cstdio>

#include "tetris.hpp"

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
}