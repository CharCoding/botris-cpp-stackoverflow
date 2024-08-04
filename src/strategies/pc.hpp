#include "strategy.hpp"

// Avoid stacking above row 5
class PC : public Strategy {
	public:
		static vector<Move> search();
};