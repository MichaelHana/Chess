#ifndef LEVEL4_H
#define LEVEL4_H
#include <vector>
#include <utility>
#include "computer.h"

struct Move;

class Level4: public Computer {
	public:
		Level4(int color);
		Move getMove(std::vector<Move> moves) override;
		char getPromotion() override;
};

#endif
