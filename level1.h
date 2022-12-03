#ifndef LEVEL1_H
#define LEVEL1_H
#include <vector>
#include <utility>
#include "computer.h"

struct Move;

class Level1 : public Computer{
	public:
		std::pair<std::pair<int, int>, std::pair<int, int>> getMove(std::vector<Move> moves);
};

#endif