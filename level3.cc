#include <cstdlib>
#include <vector>
#include <ctime>
#include "level3.h"
#include "move.h"

Level3::Level3(int color) : Computer{ color } {};

Move Level3::getMove(std::vector<Move> moves) {
	srand(time(nullptr));
	
	std::vector<Move> filter;

	for (auto i : moves) {
		if (!i.check && !i.capture.first && !i.checkmate) {
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
