#include <cstdlib>
#include <vector>
#include "level1.h"
#include "move.h"

Level1::Level1(int color) : Computer{ color } {};

Move Level1::getMove(std::vector<Move> moves) {

	int random = rand() % moves.size();

	return moves[random];
}
