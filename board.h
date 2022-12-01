#ifndef BOARD_H
#define BOARD_H
#include <utility>
#include <vector>

struct Move;
class Piece;

class Board {
	int row, col;
	Piece** pieces;
	public:
		Board(row, col, Piece** pieces);
		bool checkMove(Move m);
		std::vector<std::vector<char>> getState();
		std::vector<Move> listMoves(int colour);
};

#endif