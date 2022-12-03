#ifndef LEVEL2_H
#define LEVEL2_H
#include <vector>
#include <utility>
#include "computer.h"

struct Move;

class Level2 : public Computer {
	public:
		Level2(int color);
		Move getMove(std::vector<Move> moves);
};

#endif
