#include <cstdlib>
#include <ctime>
#include <vector>
#include "level1.h"
#include "move.h"

Level1::Level1(int color) : Computer{ color } {};

Move Level1::getMove(std::vector<Move> moves) {
	srand(time(nullptr));

	int random = rand() % moves.size();

	return moves[random];
}

char Level1::getPromotion() {
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
