#ifndef MOVE_H
#define MOVE_H
#include <utility>

class Piece;

struct Move {
	std::pair<int, int> start;
	std::pair<int, int> end;
	Piece* capture;
};

#endif
