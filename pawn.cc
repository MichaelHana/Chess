#include "pawn.h"
#include "piece.h"
#include "board.h"
#include "move.h"
#include <stdlib.h>

Pawn::Pawn(int color) : Piece(color) {}

Move Pawn::checkMove(Board* board, std::pair<int, int> start, std::pair<int, int> end) {
	// assumed that board checks move is in bounds
	// todo: en passent

	if (color == 0) { // white
		if (start.first - end.first == 0) { // vertical move: not a capture
			if (end.second - start.second < -2 || end.second - start.second > -1) { // too far or wrong direction
				return nullptr;
			} else if (end.second - start.second == -2) { // two spaces
				if (moved) { // already moved
					return nullptr;
				} else if (board->getPiece(std::make_pair(start.first, start.second - 1)) != nullptr) { // piece in the way
					return nullptr;
				} else if (board->getPiece(end) != nullptr) { // piece in the way
					return nullptr;
				}
			} else if (end.second - start.second == -1) { // one space
				if (board->getPiece(end) != nullptr) { // blocked
					return nullptr;
				}
			}
		} else if (abs(start.first - end.first) == 1 && end.second - start.second == -1) { // diagonal move: capture
			if (board->getPiece(end) == nullptr) { // no piece to capture
				return nullptr;
			} else if (board->getPiece(end)->getColor() == color) { // friendly piece to capture
				return nullptr;
			}
		} else { // invalid move
			return nullptr;
		}
	} else if (color == 1) {
		if (start.first - end.first == 0) { // vertical move: not a capture
			if (end.second - start.second < 2 || end.second - start.second > 1) { // too far or wrong direction
				return nullptr;
			} else if (end.second - start.second == 2) { // two spaces
				if (moved) { // already moved
					return nullptr;
				} else if (board->getPiece(std::make_pair(start.first, start.second + 1)) != nullptr) { // piece in the way
					return nullptr;
				} else if (board->getPiece(end) != nullptr) { // piece in the way
					return nullptr;
				}
			} else if (end.second - start.second == 1) { // one space
				if (board->getPiece(end) != nullptr) { // blocked
					return nullptr;
				}
			}
		} else if (abs(start.first - end.first) == 1 && end.second - start.second == 1) { // diagonal move: capture
			if (board->getPiece(end) == nullptr) { // no piece to capture
				return nullptr;
			} else if (board->getPiece(end)->getColor() == color) { // friendly piece to capture
				return nullptr;
			}
		} else { // invalid move
			return nullptr;
		}
	}

	return Move(start, end, board->getPiece(end));
}
