#include "strategy.hpp"

// Avoid column 10 except for I piece
class Stride90 : public Strategy {
	public:
	static vector<Move> search();
};
