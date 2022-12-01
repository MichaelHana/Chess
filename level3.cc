#include <cstdlib>
#include <vector>
#include "level3.h"

std::pair<std::pair<int, int>, std::pair<int, int>> Level2::getMove(std::vector<Move> moves) {
	std::vector<Move> filter;

	for (auto i : moves) {
		if (!i.check && !i.capture && !i.checkmate) {
			filter.emplace_back(*i);
		}
	}

	srand(time(NULL));

	if (filter.size() > 0) {
		int random = rand() % filter.size();
		return make_pair{ filter[random].start, filter[random].end };
	}

	int random = rand() % moves.size();
	return make_pair{ moves[random].start, moves[random].end };
}