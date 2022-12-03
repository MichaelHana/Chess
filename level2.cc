#include <cstdlib>
#include <vector>
#include "level2.h"
#include "move.h"

Level2::Level2(int color) : Computer{ color } {};

Move Level2::getMove(std::vector<Move> moves) {
	std::vector<Move> filter;
	
	for (auto i: moves) {
		if (i.check || i.capture || i.checkmate) {
			filter.emplace_back(i);
		}
	}

	if (filter.size() > 0) {
		int random = rand() % filter.size();
		return filter[random];
	}

	int random = rand() % moves.size();
	return moves[random];
}