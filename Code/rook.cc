#include "rook.h"
#include "piece.h"
#include "board.h"
#include <stdlib.h>

Rook::Rook(int color) : Piece(color) {}

bool Rook::validMove(Board* board, std::pair<int, int> start, std::pair<int, int> end) {
	// check move distance and if valid direction
	if ((start.first - end.first != 0 && start.second - end.second != 0) || start == end) {
		return false;
	}

	//check if blocked by piece
	//horizontal
	int x = start.first, y = start.second;
	while (x != end.first) {
		int difference_x = end.first - start.first;

		if (x != start.first) {
			if (board->getPiece(std::make_pair(x, y))) {
				return false;
			}
		}

		if (difference_x != 0) {
			x += difference_x / abs(difference_x);
		}
	}

	//vertical
	while (y != end.second) {
		int difference_y = end.second - start.second;

		if (y != start.second) {
			if (board->getPiece(std::make_pair(x, y))) {
				return false;
			}
		}

		if (difference_y != 0) {
			y += difference_y / abs(difference_y);
		}
	}

	// check if end blocked by friendly piece
	if (board->getPiece(end) && board->getPiece(end)->getColor() == color) {
		return false;
	}
	return true;
}
