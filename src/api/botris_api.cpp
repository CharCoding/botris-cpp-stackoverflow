#include "botris_api.hpp"
#include "../tetris.hpp"
#include <vector>
#include <cstdint>

namespace botris::api {
    std::vector<PieceData> find_moves(const Board board, const PieceData current) {
        std::vector<PieceData> moves;
        Board smears[4]; // if we rearrange the O piece format, we can narrow the "self" case to only 50% of I pieces
        // which I'm not sure is worth it
    }
}
