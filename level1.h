#ifndef LEVEL1_H
#define LEVEL1_H
#include "computer.h"

class Level1 : Computer {
	public:
		std::pair<std::pair<int, int>, std::pair<int, int>> getMove(vector<Move>);
};

#endif