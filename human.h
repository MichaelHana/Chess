#ifndef HUMAN_H
#define HUMAN_H
#include <iostream>
#include <vector>
#include <utility>
#include "player.h"

struct Move;

class Human : Player {
	std::istream in;
	public: 
		Player(std::istream in);
		std::pair<std::pair<int, int>, std::pair<int, int>> getMove(std::vector<Move> moves);
};

#endif