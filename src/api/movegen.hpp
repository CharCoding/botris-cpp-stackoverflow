#include "../tetris.hpp"
#include <vector>
#include <cstdint>
#include <bit>
namespace botris::api {
std::vector<PieceData> find_moves(const Board board, const Piece current) {
  std::vector<PieceData> moves;
  Board smears[4]; // if we rearrange the O piece format, we can narrow the "self" case to only 50% of I pieces
  // which I'm not sure is worth it
  for(int r = 0; r < 4; ++r) {
    for(int i = 0; i < 4; ++i) {

    }
  }
  return moves;
}
std::vector<PieceData> find_moves_fast(const Board board, const Piece current) { // if board height <= 16 and has no soft drop opportunities
  std::vector<PieceData> moves;
  // O: 9, I: 10 + 7, S/Z: 9 + 8, L/J/T: 9 + 9 + 8 + 8
  /*
  int r = (0b11110101110100U >> (int8_t)(current * 2)) & 3;
  do {
    int lx = piece_offsets[current][r][0].x; // leftmost cell (can still be positive for I90)
    int rx = piece_offsets[current][r][3].x; // rightmost cell (non-negative)
    for(int x = -lx; x < 10 - rx; ++x) {
      int i = 0;
      int column = board[x + lx] + 1;
      int max = column >> (piece_offsets[current][r][i].y & 31) | column << (32 - (piece_offsets[current][r][i].y & 31));
      do {
        ++i;
        int column = board[x + piece_offsets[current][r][i].x] + 1;
        max |= column >> (piece_offsets[current][r][i].y & 31) | column << (32 - (piece_offsets[current][r][i].y & 31));
      } while(i < 4);
    }
  } while(r--);*/
  // naive implementation, no symmetry elimination, early exit depending on piece width
  for(int r = 0; r < 4; ++r) {
    int lx = piece_offsets[current][r][0].x; // leftmost cell (can still be positive for I90)
    const int rx = piece_offsets[current][r][3].x; // rightmost cell (non-negative)
    for(int x = -lx; x < 10 - rx; ++x) {
      int min_height = (32 - std::countl_zero((unsigned)board[x + lx])) - piece_offsets[current][r][0].y;
      int i = 0;
      while(lx < rx) {
        ++lx;
        ++i;
        while(piece_offsets[current][r][i].x < lx) {
          ++i;
        }
        int height = (32 - std::countl_zero((unsigned)board[x + lx])) - piece_offsets[current][r][i].y;
        if(height > min_height) {
          min_height = height;
        }
      }
      PieceData move = {current, (Rotation)r, (int8_t)x, (int8_t)min_height};
      moves.push_back(move);
      lx = piece_offsets[current][r][0].x;
    }
  }
  return moves;
}
constexpr bool need_softdrop(const Board board, int garbage_height) {
  for(int i = 10; i--;) {
    unsigned stack = (unsigned)board[i] >> garbage_height;
    if(stack & stack + 1) {
      return true;
    }
  }
  return false;
}
} // namespace botris::api
