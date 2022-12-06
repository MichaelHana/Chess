#ifndef LEVEL1_H
#define LEVEL1_H
#include <vector>
#include <utility>
#include "computer.h"

struct Move;

class Level1 : public Computer{
	public:
		Level1(int color);
		Move getMove(std::vector<Move> moves);
		char getPromotion();
};

#endif
