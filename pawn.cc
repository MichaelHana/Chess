#include "pawn.h"
#include "piece.h"
#include "board.h"
#include <stdlib.h>

Pawn::Pawn(int color) : Piece{color}, can_be_enpassant{false} {}

bool Pawn::validMove(Board* board, std::pair<int, int> start, std::pair<int, int> end) {
	// assumed that board checks move is in bounds
	// todo: en passent

	if (color == 0) { // white
		if (start.first - end.first == 0) { // vertical move: not a capture
			if (end.second - start.second < -2 || end.second - start.second > -1) { // too far or wrong direction
				return false;
			} else if (end.second - start.second == -2) { // two spaces
				if (moved) { // already moved
					return false;
				} else if (board->getPiece(std::make_pair(start.first, start.second - 1))) { // piece in the way
					return false;
				} else if (board->getPiece(end)) { // piece in the way
					return false;
				}
			} else if (end.second - start.second == -1) { // one space
				if (board->getPiece(end)) { // blocked
					return false;
				}
			}
		} else if (abs(start.first - end.first) == 1 && end.second - start.second == -1) { // diagonal move: capture
			if (!board->getPiece(end)) { // no piece to capture
				Piece *piece = board->getPiece(std::make_pair(end.first, start.second));
				if (piece && piece->getColor() != color) {
					Pawn *p = dynamic_cast<Pawn *>(piece);
					if (p && p->getEnPassant()) {
						return true;
					}
				}
				return false;
			} else if (board->getPiece(end)->getColor() == color) { // friendly piece to capture
				return false;
			}
		} else { // invalid move
			return false;
		}
	} else if (color == 1) { // black
		if (start.first - end.first == 0) { // vertical move: not a capture
			if (end.second - start.second > 2 || end.second - start.second < 1) { // too far or wrong direction
				return false;
			} else if (end.second - start.second == 2) { // two spaces
				if (moved) { // already moved
					return false;
				} else if (board->getPiece(std::make_pair(start.first, start.second + 1))) { // piece in the way
					return false;
				} else if (board->getPiece(end)) { // piece in the way
					return false;
				}
			} else if (end.second - start.second == 1) { // one space
				if (board->getPiece(end) != nullptr) { // blocked
					return false;
				}
			}
		} else if (abs(start.first - end.first) == 1 && end.second - start.second == 1) { // diagonal move: capture
			if (!board->getPiece(end)) { // no piece to capture
				Piece *piece = board->getPiece(std::make_pair(end.first, start.second));
				if (piece && piece->getColor() != color) {
					Pawn *p = dynamic_cast<Pawn *>(piece);
					if (p && p->getEnPassant()) {
						return true;
					}
				}
				return false;
			} else if (board->getPiece(end)->getColor() == color) { // friendly piece to capture
				return false;
			}
		} else { // invalid move
			return false;
		}
	}

	return true;
}

bool Pawn::getEnPassant() {
	return can_be_enpassant;
}

void Pawn::setEnPassant(bool b) {
	can_be_enpassant = b;
}
