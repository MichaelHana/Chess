#include "queen.h"
#include "piece.h"
#include "board.h"
#include "move.h"
#include <stdlib.h>

Queen::Queen(int color) : Piece(color) {}

Move Queen::checkMove(Board* board, std::pair<int, int> start, std::pair<int, int> end) {
	// assumed that board checks move is in bounds

	// check move distance
	if (start == end) {
		return nullptr;
	} else if (start.first - end.first != 0 && start.second - end.second != 0) {
		if (abs(start.first - end.first) != abs(start.second - end.second)) {
			return nullptr;
		}
	}
	// check if blocked by piece before end
	for (int x = start.first, y = start.second; x != end.first || y != end.second; x += (end.first - start.first) / abs(end.first - start.first), y += (end.second - start.second) / abs(end.second - start.second)) {
		if (board->getPiece(std::make_pair(x, y)) != nullptr) {
			return nullptr;
		}
	}
	// check if end blocked by friendly piece
	if (board->getPiece(end) != nullptr && board->getPiece(end)->getColor() == color) {
		return nullptr;
	}

	return Move(start, end, board->getPiece(end));
}
