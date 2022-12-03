#ifndef PLAYER_H
#define PLAYER_H
#include <utility>
#include <vector>

struct Move;

class Player {
	int color;
	public:
		Player(int color);
		int getColor();
		virtual Move getMove(std::vector<Move> moves) = 0;
};

#endif