#pragma once
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

// have you seen https://tetris.wiki/Super_Rotation_System
// I'm copying from https://github.com/newclarityex/libtris/blob/main/src/utils.ts
// ohh
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

using Board = uint8_t[20][10];

Board board = {{0}};

// do we want to do a top-left piece position scheme if we're copying from nuke's code
// or does it not matter
// (i still don't completely get the piece scheme you documented up there)
// i meant in order to avoid bugs because it would more closely match nuke's code
// ok
// it shouldn't matter in theory since we don't really need to read our own board
// we'll do this for now, idk if it will work but this will be a lot of trial and error anyway
// my naming convention is very messed up here
typedef struct pieceData {
  Piece piece;
  Rotation rot = ROTATE_0;
  int x;
  int y;
} pieceData;

/**
 * Check if piece collides with any minos on the board, or is out of bounds.
 * Returns true if can be placed at current position without oob or collisions, false otherwise.
 */
constexpr bool check_piece_placeable(const Board board, const pieceData p) { // @danlliu should we use references for const Board?
  int x = p.x + pieces[p.piece][p.rot];
  int y = p.y + pieces[p.piece][p.rot];
  if(x < 0 || x > 9 || y < 0 || board[y][x]) {
    return false;
  }
  for(int i = 1; i < 7; ++i) {
    x = p.x + pieces[p.piece][p.rot + i];
    y = p.y + pieces[p.piece][p.rot + ++i];
    if(x < 0 || x > 9 || y < 0 || board[y][x]) {
      return false;
    }
  }
  return true;
}

/**
 * Check if piece p can be rotated to new rotation r (decide: should r be new rotation state or rotation direction?)
 * on success, new pieceData is returned, with p.rot == r
 * on failure, p is returned as is, with p.rot != r
 */
constexpr pieceData spin(const Board board, const pieceData p, const Rotation r) {
  pieceData rotated = p;
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
constexpr bool check_piece_immobile(const Board board, pieceData p) {
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
 * (Not tested! could be buggy)
 */
int clear_lines(Board board) {
  int delta = 0;
  for(int i = 0; i < 20; ++i) {
    bool filled = true;
    for(int j = 0; j < 10; ++j) {
      if(board[i][j] == 0) {
        filled = false;
        break;
      }
    }
    if(filled) {
      ++delta;
    } else if(delta) {
      for(int j = 0; j < 10; ++j) {
        board[i - delta][j] = board[i][j];
      }
    }
  }
  for(int i = 20 - delta; i < 20; ++i) { // can optimize here if we know the board's max height
    for(int j = 0; j < 10; ++j) {
      board[i][j] = 0;
    }
  }
  return delta;
}

/**
 * Place piece p on board, mutating board (discuss: should we return a new board copy isntead?)
 */
void place_piece(Board board, const pieceData p) {
  // check if piece can be placed?
  board[p.y + pieces[p.piece][p.rot]][p.x + pieces[p.piece][p.rot]] = 1;
  for(int i = 1; i < 7; ++i) {
    board[p.y + pieces[p.piece][p.rot + i]][p.x + pieces[p.piece][p.rot + ++i]] = 1;
  }
  clear_lines(board); // should this always be done?
}