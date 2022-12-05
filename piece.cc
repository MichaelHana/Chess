#include "piece.h"

Piece::Piece(int color) : color(color), moved{false} {}

int Piece::getColor() {
	return color;
}

void Piece::setMoved() {
	moved = true;
}

bool Piece::getMoved() {
	return moved;
}
