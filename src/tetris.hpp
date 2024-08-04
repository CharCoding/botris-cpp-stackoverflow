#include <cstdint>

enum Rotation {
  ROTATE_0 = 0,
  ROTATE_90 = 8,    // CW
  ROTATE_180 = 16,  // 180
  ROTATE_270 = 24   // CCW
};

enum Piece {
  PIECE_I = 0,
  PIECE_J = 1,
  PIECE_L = 2,
  PIECE_O = 3,
  PIECE_S = 4,
  PIECE_T = 5,
  PIECE_Z = 6,
  PIECE_NONE = 7
};

/*
so in this cursed system I use
pieces[PIECE_X][ROTATE_N] is an array of 7 ints
the first int is the 'center' of the piece, which has the same x and y offset
the next 6 ints are the x and y offsets of the other blocks of the piece
it's not very readable

I think they said the 'piece location' is the top left corner instead of the rotation center... which is annoying
 */

// Int8Array.of(1, 0, 0, 1, 0, 0, 1,32, 1, 0, 0, 0, 1, 1, 0,16, 1, 0, 0, 1, 0, 0, 1,32, 1, 0, 0, 0, 1, 1, 0),
// Int8Array.of(1, 2, 1, 0, 1,-1, 1,16, 1, 1,-1, 1, 2, 1, 0,16, 0,-1, 0, 2, 0, 1, 0,48, 0, 0, 2, 0, 1, 0,-1),
// Int8Array.of(0, 0, 1, 1, 0,-1, 0,16, 0, 1, 0, 0, 1, 0,-1,16, 0, 0,-1, 1, 0,-1, 0,48, 0,-1, 0, 0, 1, 0,-1),
// Int8Array.of(0, 0, 1, 1, 1,-1, 0,32, 0, 1,-1, 0, 1, 1, 0,16, 0,-1,-1, 0,-1, 1, 0,32, 0,-1, 0,-1, 1, 0,-1),
// Int8Array.of(0,-1, 1, 0, 1, 1, 0,32, 0, 1, 0, 1, 1, 0,-1,16, 0, 0,-1, 1,-1,-1, 0,32, 0,-1,-1, 0, 1,-1, 0),
// Int8Array.of(0,-1, 1, 1, 0,-1, 0,16, 0, 1, 1, 0, 1, 0,-1,16, 0, 1,-1, 1, 0,-1, 0,48, 0,-1,-1, 0, 1, 0,-1),
// Int8Array.of(0, 1, 1, 1, 0,-1, 0,16, 0, 1,-1, 0, 1, 0,-1,16, 0,-1,-1, 1, 0,-1, 0,48, 0,-1, 1, 0, 1, 0,-1)

const int wallkicks[] = {};

const int i_wallkicks[] = {};

uint8_t board[20][10] = {0};