#ifndef HUMAN_H
#define HUMAN_H
#include <iostream>
#include "player.h"

class Human : Player {
		std::istream in;
	public: 
		std::pair<std::pair<int, int>, std::pair<int, int>> getMove(vector<Move>);
};

#endif