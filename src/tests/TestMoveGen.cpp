#include "utils.hpp"
#include "../tetris.hpp"
#include "../api/movegen.hpp"
#include <vector>
#include <cstdint>

using botris::api::find_moves;
using botris::api::find_moves_fast;

int main() {
  Board board = {
    0b1111,
    0b11,
    0b1,
    0b1111,
    0b1,
    0,
    0b11,
    0,
    0,
    0b1
  };
  print_board(board);
  for(int i = 0; i < 7; ++i) {
    std::vector<PieceData> moves = find_moves_fast(board, (Piece)i);
    for(const auto& move : moves) {
      print_piece(move);
      putchar_unlocked(' ');
    }
    putchar_unlocked('\n');
  }
}