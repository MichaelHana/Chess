#ifndef PLAYER_H
#define PLAYER_H
#include <utility>
#include <vector>

struct Move;

class Player {
	virtual std::pair<std::pair<int, int>, std::pair<int, int>> getMove(std::vector<Move> moves) = 0;
};

#endif