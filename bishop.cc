#include "bishop.h"
#include "piece.h"
#include "board.h"
#include "move.h"
#include <stdlib.h>
#include <iostream>
Bishop::Bishop(int color) : Piece(color) {}

bool Bishop::validMove(Board* board, std::pair<int, int> start, std::pair<int, int> end) {
	// assumed that board checks move is in bounds
	// check move distance
	if (abs(start.first - end.first) != abs(start.second - end.second) || start == end) {
		return false;
	}
	// check if blocked by piece before end
	/*for (int x = start.first, y = start.second; x != end.first || y != end.second; x += (end.first - start.first) / abs(end.first - start.first), y += (end.second - start.second) / abs(end.second - start.second)) {
		if (board->getPiece(std::make_pair(x, y))) {
			return false;
		}
	}*/

	int x = start.first, y = start.second;
	while (x != end.first || y != end.second) {
		int difference_x = end.first - start.first;
		int difference_y = end.second - start.second;
		
		if (difference_x != 0 && x != end.first) {
			x += difference_x / abs(difference_x);
		}

		if (difference_y != 0 && y != end.second) {
			y += difference_y / abs(difference_y);
		}

		if (x != start.first || y != start.second) {
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
