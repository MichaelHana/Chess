#include "knight.h"
#include "piece.h"
#include "board.h"
#include <stdlib.h>

Knight::Knight(int color) : Piece(color) {}

bool Knight::validMove(Board* board, std::pair<int, int> start, std::pair<int, int> end) {
	// assumed that board checks move is in bounds

	// check move distance
	if (!(abs(start.first - end.first) == 2 && abs(start.second - end.second) == 1) && !(abs(start.first - end.first) == 1 && abs(start.second - end.second) == 2)) {
		return false;
	}
	// check if blocked by friendly piece
	if (board->getPiece(end) != nullptr && board->getPiece(end)->getColor() == color) {
		return false;
	}

	return true;
}
