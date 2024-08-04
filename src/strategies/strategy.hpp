#pragma once
#include "../api/botris_api.hpp"

using Move = botris::api::Move;
using GameState = botris::api::GameState;

class Strategy {
	// Board, current, held, queue, incoming garbage
	static vector<Move> search(GameState &g);
};

