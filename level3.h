#ifndef LEVEL3_H
#define LEVEL3_H
#include <vector>
#include <utility>
#include "computer.h"

struct Move;

class Level3: public Computer {
	public:
		Level3(int color);
		Move getMove(std::vector<Move> moves);
		char getPromotion();
};

#endif
