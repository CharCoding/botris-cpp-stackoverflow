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
constexpr int8_t wallkicks[] = {1, 0, 1, -1, 0, 2, 1, 2};

constexpr int8_t i_wallkicks[][8] = {
  {-2, 0, 1, 0, -2, -1, 1, 2},
  {-1, 0, 2, 0, -1, 2, 2, -1}
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
bool check_piece_collision(Board board, pieceData p);
/**
 * Check if piece p can be rotated to new rotation r (decide: should r be new rotation state or rotation direction?)
 * on success, new pieceData is returned, with p.rot == r
 * on failure, p is returned as is, with p.rot != r
 */
pieceData spin(Board board, pieceData p, Rotation r) {
  pieceData rotated = p;
  rotated.rot = r;
  /*
  0 -> 8 & 16 -> 8: -x +y
  
  */
  if(p.piece == Piece::PIECE_I) {
   
  } else { // please do not rotate an O piece
    if(check_piece_collision(board, rotated)) {
      return rotated;
    }
    for(int i = 0; i < 8; i += 2) {
      rotated.x = p.x + wallkicks[i];
      rotated.y = p.y + wallkicks[i + 1];
      if(check_piece_collision(board, rotated)) {
        return rotated;
      }
    }
  }
  return p;
}

struct Coord {
  int x;
  int y;
};
/**
 * Check if piece collides with any minos on the board, or is out of bounds.
 * Returns true if can be placed at current position without oob or collisions, false otherwise.
 */
bool check_piece_collision(Board board, pieceData p) {
  Coord positions[4] {
    Coord {p.x + pieces[p.piece][p.rot], p.y + pieces[p.piece][p.rot]},
    Coord {p.x + pieces[p.piece][p.rot + 1], p.y + pieces[p.piece][p.rot + 2]},
    Coord {p.x + pieces[p.piece][p.rot + 3], p.y + pieces[p.piece][p.rot + 4]},
    Coord {p.x + pieces[p.piece][p.rot + 5], p.y + pieces[p.piece][p.rot + 6]},
  };
  for (Coord c : positions) {
    if (c.x < 0 || c.x > 10 || c.y < 0 || board[c.y][c.x]) {
      return false;
    }
  }
  return true;
}

/**
 * Check if a piece cannot move in any direction (including upwards), which indicates it satisfies an all-spin
 */
bool check_piece_immobile(Board board, pieceData p) {
  p.x++;
  if(check_piece_collision(board, p)) {
    return false;
  }
  p.x -= 2;
  if(check_piece_collision(board, p)) {
    return false;
  }
  p.x++;
  p.y++;
  if(check_piece_collision(board, p)) {
    return false;
  }
  p.y -= 2;
  if(check_piece_collision(board, p)) {
    return false;
  }
  return true;
}

// For testing; note y is subtracted from coordinate due to y increase downward in the terminal, and x is doubled to print []
void print_piece(Piece p, Rotation r, int row, int col) {
  // piece[p][r] is the rotation center; I and O pieces should work the same
  //                                   Y                       X
  printf("\033[%d;%dH[]", col - pieces[p][r    ], row + pieces[p][r    ] * 2);
  printf("\033[%d;%dH[]", col - pieces[p][r | 2], row + pieces[p][r | 1] * 2);
  printf("\033[%d;%dH[]", col - pieces[p][r | 4], row + pieces[p][r | 3] * 2);
  printf("\033[%d;%dH[]", col - pieces[p][r | 6], row + pieces[p][r | 5] * 2);
}