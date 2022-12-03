#ifndef BOARD_H
#define BOARD_H
#include <utility>
#include <vector>

struct Move;
class Piece;

class Board {
	int row, col;
	Piece*** pieces;
	char** board;
	public:
		Board(int row, int col, char** board);
		bool checkMove(Move m);
		char** getState();
		Piece* getPiece(std::pair<int, int> coords);
		bool check(int king_color);
		int checkmate(int color);
		std::vector<Move> listMoves(int color);
		~Board();
};

#endif