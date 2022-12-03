#ifndef LEVEL3_H
#define LEVEL3_H
#include <vector>
#include <utility>
#include "computer.h"

struct Move;

class Level3: public Computer {
	public:
		std::pair<std::pair<int, int>, std::pair<int, int>> getMove(std::vector<Move> moves);
};

#endif