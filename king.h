#ifndef KING_H
#define KING_H
#include "piece.h"

class King : public Piece {
public:
	King(int color);
	bool validMove(Board* board, std::pair<int, int> start, std::pair<int, int> end);
};

#endif
