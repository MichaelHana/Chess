#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn : public Piece {
public:
	Pawn(int color);
	bool validMove(Board* board, std::pair<int, int> start, std::pair<int, int> end);
};

#endif
