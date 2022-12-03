#include "bishop.h"
#include "piece.h"
#include "board.h"
#include "move.h"
#include <stdlib.h>

Bishop::Bishop(int color) : Piece(color) {}

bool Bishop::validMove(Board* board, std::pair<int, int> start, std::pair<int, int> end) {
	// assumed that board checks move is in bounds

	// check move distance
	if (abs(start.first - end.first) != abs(start.second - end.second) || start == end) {
		return false;
	}
	// check if blocked by piece before end
	for (int x = start.first, y = start.second; x != end.first || y != end.second; x += (end.first - start.first) / abs(end.first - start.first), y += (end.second - start.second) / abs(end.second - start.second)) {
		if (board->getPiece(std::make_pair(x, y)) != false) {
			return false;
		}
	}
	// check if end blocked by friendly piece
	if (board->getPiece(end) != false && board->getPiece(end)->getColor() == color) {
		return false;
	}

	return true;
}
