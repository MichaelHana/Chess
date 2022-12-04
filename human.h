#ifndef HUMAN_H
#define HUMAN_H
#include <iostream>
#include <vector>
#include <utility>
#include "player.h"

struct Move;

class Human : public Player {
	std::istream &in;
	public: 
		Human(int color, std::istream &in);
		Move getMove(std::vector<Move> moves);
};

#endif
