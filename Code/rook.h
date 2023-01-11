#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece {
public:
	Rook(int color);
	bool validMove(Board* board, std::pair<int, int> start, std::pair<int, int> end);
};

#endif
