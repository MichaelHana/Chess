#ifndef PLAYER_H
#define PLAYER_H
#include <utility>
#include <vector>

struct Move;

class Player {
	protected:
		int color;
	public:
		Player(int color);
		int getColor();
		virtual Move getMove(std::vector<Move> moves) = 0;
		virtual char getPromotion() = 0;
		virtual ~Player() = default;
};

#endif
