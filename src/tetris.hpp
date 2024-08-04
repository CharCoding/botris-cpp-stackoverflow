#include <cstdint>
#include <cstdio>

enum Rotation {
  ROTATE_0 = 0,
  ROTATE_90 = 8,    // CW
  ROTATE_180 = 16,  // 180
  ROTATE_270 = 24   // CCW
};

enum Piece {
  PIECE_O = 0,
  PIECE_I = 1,
  PIECE_T = 2,
  PIECE_S = 3,
  PIECE_Z = 4,
  PIECE_J = 5,
  PIECE_L = 6  // , PIECE_G = 7  // garbage
};

constexpr char piece_letters[9] = "OITSZJLG";

#define rotate_left(r) rotate_ccw(r)
#define rotate_right(r) rotate_cw(r)
constexpr Rotation rotate_ccw(Rotation r) {
  return Rotation(r + 24 & 24);
}

constexpr Rotation rotate_cw(Rotation r) {
  return Rotation(r + 8 & 24);
}

constexpr int parity(Piece p) {
  return p == Piece::PIECE_T;
}

constexpr int column_parity(Piece p, Rotation r, int x, int y) {
  return (int)p >= 5 || (p == Piece::PIECE_T && ((int)r & 8));
}
/*
so in this cursed system I use
pieces[PIECE_X][ROTATE_N] is an array of 7 int8_t's
the first int is the 'center' of the piece, which has the same x and y offset
the next 6 ints are the x and y offsets of the other blocks of the piece
the 32/16/48/16 are special values I used for some other things, but right now they're just there for alignment
x increases to the right, y increases upward (on botris board)
it's not very readable, but the benefit is that all the rotations are precalculated

I think they said the 'piece location' is the top left corner instead of the rotation center... which is annoying
if you don't like this we can change to using a more readable format
 */
constexpr int8_t pieces[7][32] = {
  {1, 0, 0, 1, 0, 0, 1, 32, 1, 0, 0, 0, 1, 1, 0, 16, 1, 0, 0, 1, 0, 0, 1, 32, 1, 0, 0, 0, 1, 1, 0, 16},
  {1, 2, 1, 0, 1,-1, 1, 16, 1, 1,-1, 1, 2, 1, 0, 16, 0,-1, 0, 2, 0, 1, 0, 48, 0, 0, 2, 0, 1, 0,-1, 16},
  {0, 0, 1, 1, 0,-1, 0, 16, 0, 1, 0, 0, 1, 0,-1, 16, 0, 0,-1, 1, 0,-1, 0, 48, 0,-1, 0, 0, 1, 0,-1, 16},
  {0, 0, 1, 1, 1,-1, 0, 32, 0, 1,-1, 0, 1, 1, 0, 16, 0,-1,-1, 0,-1, 1, 0, 32, 0,-1, 0,-1, 1, 0,-1, 16},
  {0,-1, 1, 0, 1, 1, 0, 32, 0, 1, 0, 1, 1, 0,-1, 16, 0, 0,-1, 1,-1,-1, 0, 32, 0,-1,-1, 0, 1,-1, 0, 16},
  {0,-1, 1, 1, 0,-1, 0, 16, 0, 1, 1, 0, 1, 0,-1, 16, 0, 1,-1, 1, 0,-1, 0, 48, 0,-1,-1, 0, 1, 0,-1, 16},
  {0, 1, 1, 1, 0,-1, 0, 16, 0, 1,-1, 0, 1, 0,-1, 16, 0,-1,-1, 1, 0,-1, 0, 48, 0,-1, 1, 0, 1, 0,-1, 16},
};

constexpr int8_t wallkicks[] = {};

constexpr int8_t i_wallkicks[] = {};

uint8_t board[20][10] = {{0}};

// For testing; note y is subtracted from coordinate due to y increase downward in the terminal, and x is doubled to print []
void print_piece(Piece p, Rotation r, int row, int col) {
  // piece[p][r] is the rotation center; I and O pieces should work the same
  //                                   Y                       X
  printf("\033[%d;%dH[]", col - pieces[p][r    ], row + pieces[p][r    ] * 2);
  printf("\033[%d;%dH[]", col - pieces[p][r | 2], row + pieces[p][r | 1] * 2);
  printf("\033[%d;%dH[]", col - pieces[p][r | 4], row + pieces[p][r | 3] * 2);
  printf("\033[%d;%dH[]", col - pieces[p][r | 6], row + pieces[p][r | 5] * 2);
}