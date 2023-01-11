#include <cstdlib>
#include <vector>
#include <ctime>
#include "level3.h"
#include "move.h"

Level3::Level3(int color) : Computer{ color } {};

Move Level3::getMove(std::vector<Move> moves) {
	srand(time(nullptr));
	
	std::vector<Move> filter;

	//filter non-captures, non-checks, and non-checkmates
	for (auto i : moves) {
		if (!i.check && !i.capture.first && !i.checkmate) {
			filter.emplace_back(i);
		}
	}

	//pick a move that is not a capture, check, or checkmate
	if (filter.size() > 0) {
		int random = rand() % filter.size();
		return filter[random];
	}

	int random = rand() % moves.size();
	return moves[random];
}
