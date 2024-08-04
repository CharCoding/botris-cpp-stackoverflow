#include "strategy.hpp"

// Clear the most lines in the fewest moves
class Downstack : public Strategy {
	public:
	static vector<Move> search();
};