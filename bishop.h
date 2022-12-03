#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

class Bishop : public Piece {
public:
	Bishop(int color);
	bool validMove(Board* board, std::pair<int, int> start, std::pair<int, int> end);
};

#endif
