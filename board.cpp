#include <vector>
#include "move.h"
#include "board.h"
//#include "piece.h"

//Piece** might not be correct and might have to change how to initialize the board
/*
Board::Board(int row, int col, Piece** pieces) : row{ row }, col{ col } {
	pieces = new char[col][row];
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			this->pieces[j][i] = pieces[j][i];
		}
	}
}
*/

bool Board::checkMove(Move m) {
	return pieces[m.start.first][m.start.second]->checkMove(this, m.start, m.end);
}

std::vector<std::vector<char>> getState() {
	std::vector<std::vector<char>> char_board;

	for (auto i: pieces) {
		for (auto j : i) {
			char_board
		}
	}
}

std::vector<Move> Board::listMoves(int colour) {
	std::vector<Move> moves;
	
	//pieces not made yet so might have to rework this
	/*for (auto p : pieces) {
		for (auto m : p->listMoves(this)) {
			moves.emplace_back(m);
		}
	}*/

	return moves;
}

Board::~Board() {
	for (int i = 0; i < row; ++i) {
		delete []pieces[i];
	}
	delete []pieces;
}