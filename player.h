#ifndef PLAYER_H
#define PLAYER_H
#include <utility>
#include "move.h"

class Player {
	virtual std::pair<std::pair<int, int>, std::pair<int, int>> getMove(vector<Move>) = 0;
};

#endif