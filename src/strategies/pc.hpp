#include "strategy.hpp"

/*
A pure-pc strategy may very well require its own bot
because optimal pc theory is computationally expensive
especially with see7 instead of see11
Implementing setup+solve separately is easier than dynamically searching based on each new revealed piece
Define pc bags
1st - 7:4 (dupe: 1:6:4)
2nd - 4:7 (dupe: 1:3:7, 1:1:2:7)
3rd - 1:7:3
4th - 5:6 (dupe: 1:4:6)
5th - 2:7:2 (dupe: 1=1:7:2)
6th - 6:5 (dupe: 1:5:5)
7th - 3:7:1 (dupe: 1:2:7:1)
Define 2L transitions (+4 to pc number); for VS we should always take 2L's
2L table:
[IJLOOX]5 [IIJJOX]5 [IILLOX]5 [JJLLOX]5 [IIOOOX]5 [JJOOOX]5 [LLOOOX]5 [IIIJLX]5
Define best saves - most important on 1st, 2nd, 6th and 7th
1st - [JL]2 > 
Define bonus moves (allspin/combo/quad)
Keep track of checkerboard parity + column parity
Maybe also mod 4 parity?
 */

// Avoid stacking above row 5
class PC : public Strategy {
	public:
		static vector<Move> search();
};