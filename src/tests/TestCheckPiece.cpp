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

int main() {
  test_o();
  return 0;
}