#include <cstdlib>
#include <ctime>
#include <vector>
#include "level2.h"
#include "move.h"

Level2::Level2(int color) : Computer{ color } {};

Move Level2::getMove(std::vector<Move> moves) {
	srand(time(nullptr));
	
	std::vector<Move> filter;

	//filter capture, check, and checkmate moves	
	for (auto i: moves) {
		if (i.check || i.capture.first || i.checkmate) {
			filter.emplace_back(i);
		}
	}

	//if a capture, check, or checkmate exists
	if (filter.size() > 0) {
		int random = rand() % filter.size();
		return filter[random];
	}

	int random = rand() % moves.size();
	return moves[random];
}	
