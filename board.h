#ifndef BOARD_H
#define BOARD_H
#include <utility>
#include <vector>
#include <memory>
#include "piece.h"

struct Move;

class Board {
	int row, col;
	std::vector<std::vector<std::unique_ptr<Piece>>> pieces;
	std::vector<std::vector<char>> board;
	public:
		Board(int row, int col, std::vector<std::vector<char>> board);
		bool checkMove(Move m, bool onlyTesting = false);
		std::vector<std::vector<char>> getState();
		Piece* getPiece(std::pair<int, int> coords);
		bool check(int king_color);
		int checkmate(int color);
		std::vector<Move> listMoves(int color);
		void place(char piece, std::pair<int, int> coord);
		void remove(std::pair<int, int> coord);
		bool setupReady();
		~Board();
};

#endif
