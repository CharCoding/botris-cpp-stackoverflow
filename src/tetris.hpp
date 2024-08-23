#pragma once
#include <cstdint>
#include <vector>
#include <immintrin.h>

enum Rotation: int8_t {
  ROTATE_0 = 0,
  ROTATE_90 = 1,    // CW
  ROTATE_180 = 2,  // 180
  ROTATE_270 = 3   // CCW
};
#define ROTATE_CW ROTATE_90
#define ROTATE_CCW ROTATE_270

enum Piece: int8_t {
  PIECE_O = 0,
  PIECE_I = 1,
  PIECE_T = 2,
  PIECE_S = 3,
  PIECE_Z = 4,
  PIECE_J = 5,
  PIECE_L = 6  // , PIECE_G = 7  // garbage
};

struct Coord {
  int8_t x;
  int8_t y;
};

constexpr char piece_letters[9] = "OITSZJLG";

#define rotate_left(r) rotate_ccw(r)
#define rotate_right(r) rotate_cw(r)
constexpr Rotation rotate_ccw(Rotation r) {
  return Rotation(r + 3 & 3);
}

constexpr Rotation rotate_cw(Rotation r) {
  return Rotation(r + 1 & 3);
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

constexpr int8_t pieces[7][32] = {
  {1, 0, 0, 1, 0, 0, 1, 32, 1, 0, 0, 0, 1, 1, 0, 16, 1, 0, 0, 1, 0, 0, 1, 32, 1, 0, 0, 0, 1, 1, 0, 16},
  {1, 2, 1, 0, 1,-1, 1, 16, 1, 1,-1, 1, 2, 1, 0, 16, 0,-1, 0, 2, 0, 1, 0, 48, 0, 0, 2, 0, 1, 0,-1, 16},
  {0, 0, 1, 1, 0,-1, 0, 16, 0, 1, 0, 0, 1, 0,-1, 16, 0, 0,-1, 1, 0,-1, 0, 48, 0,-1, 0, 0, 1, 0,-1, 16},
  {0, 0, 1, 1, 1,-1, 0, 32, 0, 1,-1, 0, 1, 1, 0, 16, 0,-1,-1, 0,-1, 1, 0, 32, 0,-1, 0,-1, 1, 0,-1, 16},
  {0,-1, 1, 0, 1, 1, 0, 32, 0, 1, 0, 1, 1, 0,-1, 16, 0, 0,-1, 1,-1,-1, 0, 32, 0,-1,-1, 0, 1,-1, 0, 16},
  {0,-1, 1, 1, 0,-1, 0, 16, 0, 1, 1, 0, 1, 0,-1, 16, 0, 1,-1, 1, 0,-1, 0, 48, 0,-1,-1, 0, 1, 0,-1, 16},
  {0, 1, 1, 1, 0,-1, 0, 16, 0, 1,-1, 0, 1, 0,-1, 16, 0,-1,-1, 1, 0,-1, 0, 48, 0,-1, 1, 0, 1, 0,-1, 16},
};*/

constexpr Coord piece_offsets[7][4][4] = { // more sane representation, blocks sorted by increasing x then y
  { // O
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}}, // 0   N
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}}, // 90  E
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}}, // 180 S
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}}  // 270 W
  }, { // I
    {{-1, 1}, {0, 1}, {1, 1}, {2, 1}},
    {{1, -1}, {1, 0}, {1, 1}, {1, 2}},
    {{-1, 0}, {0, 0}, {1, 0}, {2, 0}},
    {{0, -1}, {0, 0}, {0, 1}, {0, 2}}
  }, { // T
    {{-1, 0}, {0, 0}, {0, 1}, {1, 0}},
    {{0, -1}, {0, 0}, {1, 0}, {0, 1}},
    {{-1, 0}, {0, -1}, {0, 0}, {1, 0}},
    {{-1, 0}, {0, -1}, {0, 0}, {0, 1}}
  }, { // S
    {{-1, 0}, {0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {0, 1}, {1, -1}, {1, 0}},
    {{-1, -1}, {0, -1}, {0, 0}, {1, 0}},
    {{-1, 0}, {-1, 1}, {0, -1}, {0, 0}}
  }, { // Z
    {{-1, 1}, {0, 0}, {0, 1}, {1, 0}},
    {{0, -1}, {0, 0}, {1, 0}, {1, 1}},
    {{-1, 0}, {0, -1}, {0, 0}, {1, -1}},
    {{-1, -1}, {-1, 0}, {0, 0}, {0, 1}}
  }, { // J
    {{-1, 0}, {-1, 1}, {0, 0}, {1, 0}},
    {{0, -1}, {0, 0}, {0, 1}, {1, 1}},
    {{-1, 0}, {0, 0}, {1, -1}, {1, 0}},
    {{-1, -1}, {0, -1}, {0, 0}, {0, 1}}
  }, { // L
    {{-1, 0}, {0, 0}, {1, 0}, {1, 1}},
    {{0, -1}, {0, 0}, {0, 1}, {1, -1}},
    {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}},
    {{-1, 1}, {0, -1}, {0, 0}, {0, 1}}
  }
};

// have you seen https://tetris.wiki/Super_Rotation_System
// It's basically that, but rearranged to make the bithacks work, but this won't support 180 rotations
constexpr int8_t wallkicks[64] = {
   1, 0, 1,-1, 0, 2, 1, 2,
  -1, 0,-1, 1, 0,-2,-1,-2,
   1, 0, 1,-1, 0, 2, 1, 2,
   1, 0, 1, 1, 0,-2, 1,-2,
  -1, 0,-1,-1, 0, 2,-1, 2,
  -1, 0,-1, 1, 0,-2,-1,-2,
  -1, 0,-1,-1, 0, 2,-1, 2,
   1, 0, 1, 1, 0,-2, 1,-2
};

constexpr int8_t i_wallkicks[64] = {
   2, 0,-1, 0, 2, 1,-1,-2,
  -2, 0, 1, 0,-2,-1, 1, 2,
  -1, 0, 2, 0,-1, 2, 2,-1,
  -1, 0, 2, 0,-1, 2, 2,-1,
   1, 0,-2, 0, 1,-2,-2, 1,
   1, 0,-2, 0, 1,-2,-2, 1,
  -2, 0, 1, 0,-2,-1, 1, 2,
   2, 0,-1, 0, 2, 1,-1,-2
};

constexpr int8_t o_wallkicks[64] = {

}; // cursed

struct BoardStats {
  int max_height = 0; // max 32
  float avg_height = 0; // should probably not round?
  float var_height = 0; // is this needed?
  int blocks = 0;
  int garbage_height = 0; // max 20
};

using Board = int[10];

Board board = {0};

#define get_column(b, x) (b)[(x)]
constexpr inline bool get(const Board board, int8_t x, int8_t y) { // 1 = filled, 0 = empty
  return board[x] >> y & 1;
}

constexpr bool safe_get(const Board board, int8_t x, int8_t y) {
  if(x < 0 || x > 9 || y < 0) {
    return true; // out-of-bounds = filled
  }
  return get(board, x, y);
}

inline void set(Board board, int8_t x, int8_t y) {
  board[x] |= 1 << y;
}

inline void clear(Board board, int8_t x, int8_t y) {
  board[x] &= ~(1 << y);
}



// do we want to do a top-left piece position scheme if we're copying from nuke's code
// or does it not matter
// (i still don't completely get the piece scheme you documented up there)
// i meant in order to avoid bugs because it would more closely match nuke's code
// ok
// it shouldn't matter in theory since we don't really need to read our own board
// we'll do this for now, idk if it will work but this will be a lot of trial and error anyway
// my naming convention is very messed up here
struct PieceData {
  Piece piece;
  Rotation rot;
  int8_t x;
  int8_t y;
};

/**
 * Check if piece collides with any minos on the board, or is out of bounds.
 * Does NOT check if piece is floating
 * Returns true if can be placed at current position without oob or collisions, false otherwise.
 */
constexpr bool check_piece_placeable(const Board board, const PieceData p) { // @danlliu should we use references for const Board?
  for(int i = 0; i < 4; ++i) {
    const int8_t x = p.x + piece_offsets[p.piece][p.rot][i].x;
    const int8_t y = p.y + piece_offsets[p.piece][p.rot][i].y;
    if(x < 0 || x > 10 || y < 0 || get(board, x, y)) {
      return false;
    }
  }
  return true;
}

/**
 * Check if piece p can be rotated to new rotation r (decide: should r be new rotation state or rotation direction?)
 * on success, new PieceData is returned, with p.rot == r
 * on failure, p is returned as is, with p.rot != r
 * rotate(board, PieceData, ROTATE_CW | ROTATE_CCW) automatically converts CW/CCW to target rotation of piece
 */
// v this macro doesn't work for some reason?
//#define rotate(b, p, dir) spin((b), (p), (((p).rot + (dir)) & 24)) // we should use one of these conventions
constexpr PieceData spin(const Board board, const PieceData p, const Rotation r) {
  PieceData rotated = p;
  rotated.rot = r;
  if(p.piece == Piece::PIECE_O) {
    return rotated;
  }
  if(check_piece_placeable(board, rotated)) {
    return rotated;
  } // This is not convoluted at all...
  const int8_t* const offsets = ((p.piece == Piece::PIECE_I) ? i_wallkicks : wallkicks) + ((p.rot & 16) << 1 | r);
  for(int i = 0; i < 8; ++i) {
    rotated.x = p.x + offsets[i];
    rotated.y = p.y + offsets[++i];
    if(check_piece_placeable(board, rotated)) {
      return rotated;
    }
  }
  return p;
}

/**
 * Check if a piece cannot move in any direction (including upwards), which indicates it satisfies an all-spin
 * Checking for upwards (+y) first since it is most likely to return
 */
constexpr bool check_piece_immobile(const Board board, PieceData p) {
  p.y++;
  if(check_piece_placeable(board, p)) {
    return false;
  }
  p.y -= 2;
  if(check_piece_placeable(board, p)) {
    return false;
  }
  p.y++;
  p.x++;
  if(check_piece_placeable(board, p)) {
    return false;
  }
  p.x -= 2;
  if(check_piece_placeable(board, p)) {
    return false;
  }
  return true;
}

/**
 * Clear lines of the board, starting from the bottom and working upwards, mutating board
 * Returns the number of lines cleared
 */
int clear_lines(Board board) {
  int mask = board[0];
  for(int i = 9; i; --i) {
    mask &= board[i];
  }
  int delta = __builtin_popcount(mask);
  for(int i = 0; i < 10; ++i) {
    board[i] = _pext_u32(board[i], ~mask); // not cross platform D:
  }
  return delta;
}

/**
 * Tank garbage according to the hole columns, mutating board
 * Returns the rows of garbage tanked
 * maybe should return whether bot is still alive instead? (requires getting the next piece in queue) or return void?
 */
int tank_garbage(Board board, const std::vector<unsigned> columns) {
  const int delta = columns.size();
  for(int i = 10; i--;) { // shld
    board[i] = board[i] << delta | -1U >> (32 - delta);
  }
  unsigned mask = -2; // for each row, clear a single column by anding with mask (all 1's except one), then move up by rotl
  for(int i = delta; i--;) { // this is probably faster than first converting garbage vector to (column, height)
    board[columns[i]] &= mask;
    mask = mask << 1 | mask >> 31;
  } // ok this may be slightly cursed
  return delta;
}

/**
 * Place piece p on board, mutating board (discuss: should we return a new board copy isntead?)
 */
void place_piece(Board board, const PieceData p) {
  for(int i = 0; i < 4; ++i) {
    set(board, p.x + piece_offsets[p.piece][p.rot][i].x, p.y + piece_offsets[p.piece][p.rot][i].y);
  }
}
