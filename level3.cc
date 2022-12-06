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

char Level3::getPromotion() {
	int random = rand() & 4;
	if (color == 0) {
		if (random == 0) {
			return 'B';
		} else if (random == 1) {
			return 'R';
		} else if (random == 2) {
			return 'N';
		} else {
			return 'Q';
		}
	} else if (color == 1) {
		if (random == 0) {
			return 'b';
		} else if (random == 1) {
			return 'r';
		} else if (random == 2) {
			return 'n';
		} else {
			return 'q';
		}
	}
	return ' ';
}
