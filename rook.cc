#include "rook.h"
#include "piece.h"
#include "board.h"
#include <stdlib.h>

Rook::Rook(int color) : Piece(color) {}

bool Rook::validMove(Board* board, std::pair<int, int> start, std::pair<int, int> end) {
	// assumed that board checks move is in bounds

	// check move distance
	if ((start.first - end.first != 0 && start.second - end.second != 0) || start == end) {
		return false;
	}

	// check if blocked by piece before end
	/*for (int x = start.first, y = start.second; x != end.first || y != end.second; x += (end.first - start.first) / abs(end.first - start.first), y += (end.second - start.second) / abs(end.second - start.second)) {
		if (board->getPiece(std::make_pair(x, y))) {
			return false;
		}
	}*/

	int x = start.first, y = start.second;
	while (x != end.first) {
		int difference_x = end.first - start.first;

		if (difference_x != 0) {
			x += difference_x / abs(difference_x);
		}

		if (x != start.first) {
			if (board->getPiece(std::make_pair(x, y))) {
				return false;
			}
		}
	}

	while (y != end.second) {
		int difference_y = end.second - start.second;

		if (difference_y != 0) {
			y += difference_y / abs(difference_y);
		}

		if (y != start.second) {
			if (board->getPiece(std::make_pair(x, y))) {
				return false;
			}
		}
	}

	// check if end blocked by friendly piece
	if (board->getPiece(end) && board->getPiece(end)->getColor() == color) {
		return false;
	}

	return true;
}
