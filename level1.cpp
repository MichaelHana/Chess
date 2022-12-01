#include <cstdlib>
#include <vector>
#include "level1.h"

std::pair<std::pair<int, int>, std::pair<int, int>> Level1::getMove(std::vector<Move> moves) {
	srand(time(NULL));

	int random = rand() % moves.size();

	return make_pair{ moves[random].start, moves[random].end };
}