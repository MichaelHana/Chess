#include "king.h"
#include "piece.h"
#include "board.h"
#include "rook.h"
#include <stdlib.h>

King::King(int color) : Piece(color) {}

bool King::validMove(Board* board, std::pair<int, int> start, std::pair<int, int> end) {
	// assumed that board checks move is in bounds
	// todo: castling

	// check move distance
	int x = abs(start.first - end.first);
	int y = abs(start.second - end.second);
	
	//castling
	if (x == 2 && y == 0 && moved == false) {
		std::pair<int, int> king_rook = std::make_pair(7, 7);
		std::pair<int, int> queen_rook = std::make_pair(0, 7);
		if (board->getPiece(king_rook) && !board->getPiece(king_rook)->getMoved() && dynamic_cast<Rook *>(board->getPiece(king_rook))) {
			if (!board->getPiece(std::make_pair(6, 7)) && !board->getPiece(std::make_pair(5, 7))) {
				return true;
			}
		}

		if (board->getPiece(queen_rook) && !board->getPiece(queen_rook)->getMoved() && dynamic_cast<Rook *>(board->getPiece(queen_rook))) {
			if (!board->getPiece(std::make_pair(1, 7)) && !board->getPiece(std::make_pair(2, 7)) && !board->getPiece(std::make_pair(3, 7))) {
				return true;
			}
		}
	}

	//move distance
	if ((x != 1 && x != 0) || (y != 1 && y != 0) || start == end) {
		return false;
	}
	// check if blocked by friendly piece
	if (board->getPiece(end) && board->getPiece(end)->getColor() == color) {
		return false;
	}

	return true;
}
