#include <cstdlib>
#include <vector>
#include "level1.h"
#include "move.h"

std::pair<std::pair<int, int>, std::pair<int, int>> Level1::getMove(std::vector<Move> moves) {

	int random = rand() % moves.size();

	return std::make_pair( moves[random].start, moves[random].end );
}
