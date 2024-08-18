#pragma once
#undef NDEBUG
#include <cassert>

#include "../tetris.hpp"
#include "utils.cpp"

void test_o() {
  pieceData p;
  Board b = {
      {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},  // 0
      {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},  // 1
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 2
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 3
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 4
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 5
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 6
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 7
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 8
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 9
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 10
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 11
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 12
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 13
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 14
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 15
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 16
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 17
      {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},  // 18
      {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},  // 19
  };
  p.piece = PIECE_O;
  p.rot = ROTATE_0;

  p.x = 0;
  p.y = 0;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_90;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_180;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_270;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_0;
  p.x++;
  assert(!check_piece_placeable(b, p));
  p.y++;
  assert(!check_piece_placeable(b, p));
  p.x--;
  assert(!check_piece_placeable(b, p));

  p.x = 8;
  p.y = 18;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_90;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_180;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_270;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_0;
  p.y++;
  assert(!check_piece_placeable(b, p));
  p.x++;
  assert(!check_piece_placeable(b, p));
  p.y--;
  assert(!check_piece_placeable(b, p));

  p.x = 8;
  p.y = 0;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_90;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_180;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_270;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_0;
  p.y++;
  assert(!check_piece_placeable(b, p));
  p.x++;
  assert(!check_piece_placeable(b, p));
  p.y--;
  assert(!check_piece_placeable(b, p));

  p.x = 0;
  p.y = 18;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_90;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_180;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_270;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_0;
  p.y++;
  assert(!check_piece_placeable(b, p));
  p.x++;
  assert(!check_piece_placeable(b, p));
  p.y--;
  assert(!check_piece_placeable(b, p));

  p.x = 4;
  assert(!check_piece_placeable(b, p));
  p.y = 9;
  assert(!check_piece_placeable(b, p));
}

void test_i() {
  Board b = {
      {0, 0, 0, 0, 1, 1, 1, 1, 1, 0},  // 0
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 1
      {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 2
      {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 3
      {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 4
      {0, 1, 1, 1, 1, 1, 0, 0, 0, 0},  // 5
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 6
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 7
      {1, 1, 0, 0, 0, 0, 1, 1, 1, 1},  // 8
      {1, 1, 0, 0, 0, 0, 1, 1, 1, 1},  // 9
      {1, 1, 0, 0, 0, 0, 1, 1, 1, 1},  // 10
      {1, 1, 0, 0, 0, 0, 1, 1, 1, 1},  // 11
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 12
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 13
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 14
      {1, 1, 1, 1, 1, 1, 1, 0, 1, 1},  // 15
      {1, 1, 1, 1, 1, 1, 1, 0, 1, 1},  // 16
      {1, 1, 0, 0, 0, 0, 1, 0, 1, 1},  // 17
      {1, 1, 1, 1, 1, 1, 1, 0, 1, 1},  // 18
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // 19
  };

  pieceData p;
  p.piece = PIECE_I;
  p.rot = ROTATE_0;
  p.x = 3;
  for (p.y = 7; p.y < 11; p.y++) {
    assert(check_piece_placeable(b, p));
  }
  p.y = 11;
  assert(!check_piece_placeable(b, p));
  p.y = 6;
  assert(!check_piece_placeable(b, p));
  p.y = 8;
  p.x = 2;
  assert(!check_piece_placeable(b, p));
  p.x = 4;
  assert(!check_piece_placeable(b, p));

  p.rot = ROTATE_180;
  p.x = 3;
  for (p.y = 8; p.y < 12; p.y++) {
    assert(check_piece_placeable(b, p));
  }
  p.y = 12;
  assert(!check_piece_placeable(b, p));
  p.y = 7;
  assert(!check_piece_placeable(b, p));
  p.y = 9;
  p.x = 2;
  assert(!check_piece_placeable(b, p));
  p.x = 4;
  assert(!check_piece_placeable(b, p));

  p.rot = ROTATE_90;
  p.y = 9;
  for (p.x = 1; p.x < 5; p.x++) {
    assert(check_piece_placeable(b, p));
  }
  p.x = 0;
  assert(!check_piece_placeable(b, p));
  p.x = 5;
  assert(!check_piece_placeable(b, p));
  p.x = 2;
  p.y = 8;
  assert(!check_piece_placeable(b, p));
  p.y = 10;
  assert(!check_piece_placeable(b, p));

  p.rot = ROTATE_270;
  p.y = 9;
  for (p.x = 2; p.x < 6; p.x++) {
    assert(check_piece_placeable(b, p));
  }
  p.x = 1;
  assert(!check_piece_placeable(b, p));
  p.x = 6;
  assert(!check_piece_placeable(b, p));
  p.x = 3;
  p.y = 10;
  assert(!check_piece_placeable(b, p));
  p.y = 8;
  assert(!check_piece_placeable(b, p));

  p.x = 0;
  p.y = 0;
  p.rot = ROTATE_0;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_180;
  assert(!check_piece_placeable(b, p));
  p.x = 1;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_0;
  assert(!check_piece_placeable(b, p));
  p.y = -1;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_180;
  assert(!check_piece_placeable(b, p));

  p.x = 8;
  p.y = 5;
  p.rot = ROTATE_0;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_180;
  assert(!check_piece_placeable(b, p));
  p.x = 7;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_0;
  assert(!check_piece_placeable(b, p));
  p.y = 4;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_180;
  assert(!check_piece_placeable(b, p));

  p.x = -1;
  p.y = 3;
  p.rot = ROTATE_90;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_270;
  assert(!check_piece_placeable(b, p));
  p.x = 0;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_90;
  assert(!check_piece_placeable(b, p));

  p.x = 8;
  p.y = 1;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_270;
  assert(!check_piece_placeable(b, p));
  p.x = 9;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_90;
  assert(!check_piece_placeable(b, p));
}

int main() {
  test_o();
  test_i();
  return 0;
}