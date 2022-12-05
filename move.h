#ifndef MOVE_H
#define MOVE_H
#include <utility>

class Piece;

struct Move {
	std::pair<int, int> start;
	std::pair<int, int> end;
	bool capture;
	bool check;
	bool checkmate;
	int castle; //0 = no castle, 1 = king side castle, 2 = queen side castle
	std::pair<bool, char> promote;
};

#endif
