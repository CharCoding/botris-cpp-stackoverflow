
#pragma once

#include "../tetris.hpp"
#include "botris.hpp"
#include "json.hpp"

namespace botris::api {

enum class Move : uint8_t {
  Hold,
  Left,
  Right,
  DASLeft,
  DASRight,
  CW,
  CCW,
  Down,
  InfDrop
};

struct GameState {
  Board board;
  std::array<Piece, 6> queue;
  std::vector<unsigned> garbage;
  std::optional<Piece> held;
  pieceData current;
  unsigned combo;
  unsigned score;
  unsigned pieces;
  bool canHold;
  bool b2b;
  bool dead;
};

constexpr const char *moveToString(Move move) {
  switch (move) {
  case Move::Hold:
    return "hold";
  case Move::Left:
    return "move_left";
  case Move::Right:
    return "move_right";
  case Move::DASLeft:
    return "sonic_left";
  case Move::DASRight:
    return "sonic_right";
  case Move::CW:
    return "rotate_cw";
  case Move::CCW:
    return "rotate_ccw";
  case Move::Down:
    return "drop";
  case Move::InfDrop:
    return "sonic_drop";
  }
}

inline void sendMove(const std::span<Move> &moves) {
  auto cmd = nlohmann::json::array();
  for (auto m : moves) {
    cmd.push_back(moveToString(m));
  }
  auto data = nlohmann::json::object(
      {{"type", "action"},
       {"payload", nlohmann::json::object({{"commands", cmd}})}});
  webSocket.send(data.dump());
}

inline GameState parseGameState(const nlohmann::json &gameState) {
  GameState result;

  auto pieceCharToType = [](char c) -> Piece {
    switch (c) {
    case 'O':
      return PIECE_O;
    case 'I':
      return PIECE_I;
    case 'T':
      return PIECE_T;
    case 'S':
      return PIECE_S;
    case 'Z':
      return PIECE_Z;
    case 'J':
      return PIECE_J;
    case 'L':
      return PIECE_L;
    default:
      assert(false);
    }
  };

  { // board
    for (auto r = 0; r < 20; ++r) {
      for (auto c = 0; c < 10; ++c) {
        auto block = gameState["board"][r][c];
        if (block.is_null())
          result.board[r][c] = 0;
        else
          result.board[r][c] = 1;
      }
    }
  }
  { // queue
    for (auto i = 0; i < 6; ++i) {
      std::string p = gameState["queue"][i];
      result.queue[i] = pieceCharToType(p[0]);
    }
  }
  { // garbage
    auto garbageQueue = gameState["garbageQueued"];
    for (auto g : garbageQueue) {
      result.garbage.push_back(g["delay"]);
    }
  }
  { // held
    auto h = gameState["held"];
    if (h.is_null()) {
      result = {};
    } else {
      std::string p = gameState["held"];
      result.held = pieceCharToType(p[0]);
    }
  }
  { // current
    std::string p = gameState["current"]["piece"];
    result.current.piece = pieceCharToType(p[0]);
    result.current.x = gameState["current"]["x"];
    result.current.x = gameState["current"]["y"];
  }
  { // quick assignables
    result.canHold = gameState["canHold"];
    result.combo = gameState["combo"];
    result.b2b = gameState["b2b"];
    result.score = gameState["score"];
    result.pieces = gameState["piecesPlaced"];
    result.dead = gameState["dead"];
  }
  return result;
}

} // namespace botris::api
