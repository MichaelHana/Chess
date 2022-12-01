#ifndef PIECE_H
#define PIECE_H
#include <utility>

class Board;
class Move;

class Piece {
	int color;
	bool moved;
public:
	Piece(int color);
	int getColor();
	void setMoved();
	virtual Move checkMove(Board* board, std::pair<int, int> start, std::pair<int, int> end) = 0;
};

#endif
