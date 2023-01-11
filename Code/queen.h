#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

class Queen : public Piece {
public:
	Queen(int color);
	bool validMove(Board* board, std::pair<int, int> start, std::pair<int, int> end) override;
};

#endif
