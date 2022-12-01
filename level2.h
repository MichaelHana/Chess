#ifndef LEVEL2_H
#define LEVEL2_H
#include <vector>
#include <utility>
#include "computer.h"

struct Move;

class Level2 : Computer {
	public:
		std::pair<std::pair<int, int>, std::pair<int, int>> getMove(std::vector<Move> moves);
};

#endif
