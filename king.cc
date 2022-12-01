#include "king.h"
#include "piece.h"
#include "board.h"
#include "move.h"
#include <stdlib.h>

King::King(int color) : Piece(color) {}

Move King::checkMove(Board* board, std::pair<int, int> start, std::pair<int, int> end) {
	// assumed that board checks move is in bounds
	// todo: castling, check

	// check move distance
	if (abs(start.first - end.first) != 1 || abs(start.second - end.second) != 1) {
		return nullptr;
	}
	// check if blocked by friendly piece
	if (board->getPiece(end) != nullptr && board->getPiece(end)->getColor() == color) {
		return nullptr;
	}

	return Move(start, end, board->getPiece(end));
}
