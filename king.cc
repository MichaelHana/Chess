#include "king.h"
#include "piece.h"
#include "board.h"
#include <stdlib.h>

King::King(int color) : Piece(color) {}

bool King::validMove(Board* board, std::pair<int, int> start, std::pair<int, int> end) {
	// assumed that board checks move is in bounds
	// todo: castling

	// check move distance
	int x = abs(start.first - end.first);
	int y = abs(start.second - end.second);
	if ((x != 1 && x != 0) || (y != 1 && y != 0) || start == end) {
		return false;
	}
	// check if blocked by friendly piece
	if (board->getPiece(end) && board->getPiece(end)->getColor() == color) {
		return false;
	}

	return true;
}
