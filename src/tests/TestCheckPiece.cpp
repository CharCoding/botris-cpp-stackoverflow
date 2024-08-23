#undef NDEBUG
#include <cassert>

#include "utils.hpp"

void test_o() {
  Board b = {
    0b00111111111111111100,
    0b00111111111111111100,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b00111111111111111100,
    0b00111111111111111100
  };
  PieceData p;
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
  p.y++; // placing pieces above row 20 is allowed
  assert(check_piece_placeable(b, p)); // although it can't be supported here, that's a different issue
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
  p.y++; // same as line 51
  assert(check_piece_placeable(b, p));
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
    0b11111111111111000010,
    0b11111111111111111110,
    0b11011111000011111110,
    0b11011111000011111110,
    0b11011111000011111111,
    0b11011111000011111111,
    0b11111111111111011111,
    0b10000111111111011111,
    0b11111111111111011111,
    0b11111111111111010000
  };
  PieceData p;
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

void washing_machine() {
  Board b = {
    0b1111000,
    0b1111010,
    0b1111000,
    0b1111111,
    0b1111111,
    0b1111111,
    0b1111111,
    0b1111111,
    0b1111111,
    0b1111111
  };
  PieceData p;
  p.piece = PIECE_J;
  p.rot = ROTATE_0;
  p.x = 0;
  p.y = 0;
  assert(!check_piece_placeable(b, p));
  p.x = 1;
  assert(check_piece_placeable(b, p));
  p.y = 1;
  assert(!check_piece_placeable(b, p));
  p.y = 2;
  assert(!check_piece_placeable(b, p));

  p.rot = ROTATE_90;
  p.x = 0;
  p.y = 0;
  assert(!check_piece_placeable(b, p));
  p.y = 1;
  assert(check_piece_placeable(b, p));
  p.x = 1;
  assert(!check_piece_placeable(b, p));
  p.x = 2;
  assert(!check_piece_placeable(b, p));

  p.rot = ROTATE_180;
  p.x = 2;
  p.y = 2;
  assert(!check_piece_placeable(b, p));
  p.x = 1;
  assert(check_piece_placeable(b, p));
  p.y = 1;
  assert(!check_piece_placeable(b, p));
  p.y = 0;
  assert(!check_piece_placeable(b, p));

  p.rot = ROTATE_270;
  p.x = 2;
  p.y = 0;
  assert(!check_piece_placeable(b, p));
  p.y = 1;
  assert(check_piece_placeable(b, p));
  p.x = 3;
  assert(!check_piece_placeable(b, p));
  p.x = 1;
  assert(!check_piece_placeable(b, p));
  p.x = 0;
  assert(!check_piece_placeable(b, p));

  p.piece = PIECE_L;
  p.rot = ROTATE_0;
  p.x = 0;
  p.y = 0;
  assert(!check_piece_placeable(b, p));
  p.x = 1;
  assert(check_piece_placeable(b, p));
  p.y = 1;
  assert(!check_piece_placeable(b, p));
  p.y = 2;
  assert(!check_piece_placeable(b, p));
  p.y = 0;
  p.x = 2;
  assert(!check_piece_placeable(b, p));

  p.rot = ROTATE_90;
  p.x = 0;
  p.y = 0;
  assert(!check_piece_placeable(b, p));
  p.y = 1;
  assert(check_piece_placeable(b, p));
  p.x = -1;
  assert(!check_piece_placeable(b, p));
  p.x = 0;
  p.y = 2;
  assert(!check_piece_placeable(b, p));
  p.x = 1;
  assert(!check_piece_placeable(b, p));
  p.x = 2;
  assert(!check_piece_placeable(b, p));

  p.rot = ROTATE_180;
  p.x = 0;
  p.y = 2;
  assert(!check_piece_placeable(b, p));
  p.x = 1;
  assert(check_piece_placeable(b, p));
  p.x = 2;
  assert(!check_piece_placeable(b, p));
  p.x = 1;
  p.y = 3;
  assert(!check_piece_placeable(b, p));
  p.y = 1;
  assert(!check_piece_placeable(b, p));
  p.y = 0;
  assert(!check_piece_placeable(b, p));

  p.rot = ROTATE_270;
  p.x = 2;
  p.y = 1;
  assert(check_piece_placeable(b, p));
  p.x = 3;
  assert(!check_piece_placeable(b, p));
  p.x = 1;
  assert(!check_piece_placeable(b, p));
  p.x = 2;
  p.y = 2;
  assert(!check_piece_placeable(b, p));
  p.y = 0;
  assert(!check_piece_placeable(b, p));
}

void test_jl() {
  Board j_holes = {
    0b110001100,
    0b110111110,
    0b111111110,
    0b111111111,
    0b111111111,
    0b111111111,
    0b111111111,
    0b110111111,
    0b110111110,
    0b110011000
  };
  Board l_holes = {
    0b110011000,
    0b110111110,
    0b110111111,
    0b111111111,
    0b111111111,
    0b111111111,
    0b111111111,
    0b111111110,
    0b110111110,
    0b110001100
  };
  PieceData j;
  j.piece = PIECE_J;
  PieceData l;
  l.piece = PIECE_L;
  j.rot = l.rot = ROTATE_0;
  j.y = l.y = 0;
  j.x = l.x = 1;
  assert(check_piece_placeable(j_holes, j));
  assert(!check_piece_placeable(j_holes, l));

  j.x = l.x = 8;
  assert(!check_piece_placeable(l_holes, j));
  assert(check_piece_placeable(l_holes, l));

  j.rot = l.rot = ROTATE_90;
  j.x = l.x = 0;
  j.y = l.y = 5;
  assert(check_piece_placeable(j_holes, j));
  assert(!check_piece_placeable(j_holes, l));

  j.y = l.y = 1;
  assert(!check_piece_placeable(l_holes, j));
  assert(check_piece_placeable(l_holes, l));

  j.rot = l.rot = ROTATE_180;
  j.x = l.x = 8;
  j.y = l.y = 6;
  assert(check_piece_placeable(j_holes, j));
  assert(!check_piece_placeable(j_holes, l));

  j.x = l.x = 1;
  assert(!check_piece_placeable(l_holes, j));
  assert(check_piece_placeable(l_holes, l));

  j.rot = l.rot = ROTATE_270;
  j.x = l.x = 9;
  j.y = l.y = 1;
  assert(check_piece_placeable(j_holes, j));
  assert(!check_piece_placeable(j_holes, l));

  j.y = l.y = 5;
  assert(!check_piece_placeable(l_holes, j));
  assert(check_piece_placeable(l_holes, l));
}

void test_s() {
  Board b = {
    0b11001,
    0b11100,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11110,
    0b11100,
    0b11101
  };
  PieceData p;
  p.piece = PIECE_S;
  p.rot = ROTATE_0;
  p.x = 8;
  p.y = 0;
  assert(check_piece_placeable(b, p));
  p.piece = PIECE_Z;
  assert(!check_piece_placeable(b, p));
  p.piece = PIECE_S;
  p.x = 9;
  assert(!check_piece_placeable(b, p));
  p.x = 7;
  assert(!check_piece_placeable(b, p));
  p.x = 8;
  p.y = -1;
  assert(!check_piece_placeable(b, p));
  p.y = 1;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_90;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_270;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_180;
  assert(check_piece_placeable(b, p));
  p.piece = PIECE_Z;
  assert(!check_piece_placeable(b, p));
  p.piece = PIECE_S;
  p.y = 0;
  assert(!check_piece_placeable(b, p));
  p.y = 1;
  p.x = 9;
  assert(!check_piece_placeable(b, p));
  p.x = 7;
  assert(!check_piece_placeable(b, p));

  p.rot = ROTATE_90;
  p.x = 0;
  p.y = 1;
  assert(check_piece_placeable(b, p));
  p.piece = PIECE_Z;
  assert(!check_piece_placeable(b, p));
  p.piece = PIECE_S;
  p.y = 0;
  assert(!check_piece_placeable(b, p));
  p.y = 2;
  assert(!check_piece_placeable(b, p));
  p.y = 1;
  p.x = -1;
  assert(!check_piece_placeable(b, p));
  p.x = 1;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_180;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_0;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_270;
  assert(check_piece_placeable(b, p));
  p.piece = PIECE_Z;
  assert(!check_piece_placeable(b, p));
  p.piece = PIECE_S;
  p.x = 2;
  assert(!check_piece_placeable(b, p));
  p.x = 0;
  assert(!check_piece_placeable(b, p));
  p.x = 1;
  p.y = 2;
  assert(!check_piece_placeable(b, p));
  p.y = 0;
  assert(!check_piece_placeable(b, p));
}

void test_z() {
  Board b = {
    0b11100,
    0b11001,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11101,
    0b11100,
    0b11110
  };
  PieceData p;
  p.piece = PIECE_Z;
  p.rot = ROTATE_0;
  p.x = 8;
  p.y = 0;
  assert(check_piece_placeable(b, p));
  p.piece = PIECE_S;
  assert(!check_piece_placeable(b, p));
  p.piece = PIECE_Z;
  p.x = 9;
  assert(!check_piece_placeable(b, p));
  p.x = 7;
  assert(!check_piece_placeable(b, p));
  p.x = 8;
  p.y = -1;
  assert(!check_piece_placeable(b, p));
  p.y = 1;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_90;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_270;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_180;
  assert(check_piece_placeable(b, p));
  p.piece = PIECE_S;
  assert(!check_piece_placeable(b, p));
  p.piece = PIECE_Z;
  p.y = 0;
  assert(!check_piece_placeable(b, p));
  p.y = 1;
  p.x = 9;
  assert(!check_piece_placeable(b, p));
  p.x = 7;
  assert(!check_piece_placeable(b, p));

  p.rot = ROTATE_90;
  p.x = 0;
  p.y = 1;
  assert(check_piece_placeable(b, p));
  p.piece = PIECE_S;
  assert(!check_piece_placeable(b, p));
  p.piece = PIECE_Z;
  p.y = 0;
  assert(!check_piece_placeable(b, p));
  p.y = 2;
  assert(!check_piece_placeable(b, p));
  p.y = 1;
  p.x = -1;
  assert(!check_piece_placeable(b, p));
  p.x = 1;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_180;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_0;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_270;
  assert(check_piece_placeable(b, p));
  p.piece = PIECE_S;
  assert(!check_piece_placeable(b, p));
  p.piece = PIECE_Z;
  p.x = 2;
  assert(!check_piece_placeable(b, p));
  p.x = 0;
  assert(!check_piece_placeable(b, p));
  p.x = 1;
  p.y = 2;
  assert(!check_piece_placeable(b, p));
  p.y = 0;
  assert(!check_piece_placeable(b, p));
}

void test_ts() { // haha you said "testes" point and laugh <-- lmao
  Board b = {
    0b1100011110,
    0b1110111100,
    0b1111111110,
    0b1111111111,
    0b1111101111,
    0b1111000111,
    0b1111101111,
    0b1101111111,
    0b1100111101,
    0b1101111000
  };
  PieceData p;
  p.piece = PIECE_T;
  p.rot = ROTATE_0;
  p.x = 1;
  p.y = 0;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_180;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_0;
  p.x = 0;
  assert(!check_piece_placeable(b, p));
  p.x = 2;
  assert(!check_piece_placeable(b, p));
  p.y = -1;
  assert(!check_piece_placeable(b, p));
  p.y = 1;
  assert(!check_piece_placeable(b, p));

  p.x = 9;
  p.y = 1;
  p.rot = ROTATE_270;
  assert(check_piece_placeable(b, p));
  p.y = 0;
  assert(!check_piece_placeable(b, p));
  p.y = 2;
  assert(!check_piece_placeable(b, p));
  p.y = 1;
  p.x = 8;
  assert(!check_piece_placeable(b, p));
  p.x = 10;
  assert(!check_piece_placeable(b, p));
  p.x = 9;
  p.rot = ROTATE_90;
  assert(!check_piece_placeable(b, p));
  p.x = 8;
  assert(!check_piece_placeable(b, p));

  p.x = 0;
  p.y = 6;
  assert(check_piece_placeable(b, p));
  p.y = 5;
  assert(!check_piece_placeable(b, p));
  p.y = 7;
  assert(!check_piece_placeable(b, p));
  p.y = 6;
  p.x = -1;
  assert(!check_piece_placeable(b, p));
  p.x = 1;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_270;
  assert(!check_piece_placeable(b, p));
  p.x = 0;
  assert(!check_piece_placeable(b, p));

  p.x = 8;
  p.y = 7;
  p.rot = ROTATE_180;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_0;
  assert(!check_piece_placeable(b, p));
  p.rot = ROTATE_180;
  p.x = 7;
  assert(!check_piece_placeable(b, p));
  p.x = 9;
  assert(!check_piece_placeable(b, p));
  p.x = 8;
  p.y = 8;
  assert(!check_piece_placeable(b, p));
  p.y = 6;
  assert(!check_piece_placeable(b, p));

  p.x = 5;
  p.y = 4;
  p.rot = ROTATE_0;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_90;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_180;
  assert(check_piece_placeable(b, p));
  p.rot = ROTATE_270;
  assert(check_piece_placeable(b, p));
}

int main() {
  test_o();
  test_i();
  washing_machine();
  test_jl();
  test_s();
  test_z();
  test_ts();
  return 0;
}