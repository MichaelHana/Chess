#include "king.h"
#include "piece.h"
#include "board.h"
#include <stdlib.h>

King::King(int color) : Piece(color) {}

bool King::validMove(Board* board, std::pair<int, int> start, std::pair<int, int> end) {
	// assumed that board checks move is in bounds
	// todo: castling

	// check move distance
	if ((abs(start.first - end.first) != 1 || abs(start.second - end.second) != 1) || start == end) {
		return false;
	}
	// check if blocked by friendly piece
	if (board->getPiece(end) && board->getPiece(end)->getColor() == color) {
		return false;
	}

	return true;
}
