#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class Knight : public Piece {
public:
	Knight(int color);
	bool validMove(Board* board, std::pair<int, int> start, std::pair<int, int> end);
};

#endif
