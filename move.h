#ifndef MOVE_H
#define MOVE_H
#include <utility>

struct Move {
	std::pair<int, int> start;
	std::pair<int, int> end;
	bool capture;
	bool check;
	bool checkmate;
};

#endif
