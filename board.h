#ifndef BOARD_H
#define BOARD_H
#include <utility>
#include <vector>
#include <memory>
#include "piece.h"

struct Move;

class Board {
	std::vector<std::vector<std::unique_ptr<Piece>>> pieces;
	std::vector<std::vector<char>> board;
	public:
		Board(int row, int col, std::vector<std::vector<char>> board);
		bool checkMove(Move m, int color, bool onlyTesting = false, char *capture = nullptr, bool *check_move = nullptr, bool *checkmate_move = nullptr, bool *castle_move = nullptr);
		std::vector<std::vector<char>> getState();
		Piece* getPiece(std::pair<int, int> coords);
		bool check(int king_color);
		int checkmate(int color);
		std::vector<Move> listMoves(int color);
		bool promote(Move m, int color);
		void place(char piece, std::pair<int, int> coord);
		void remove(std::pair<int, int> coord);
		bool setupReady();
		~Board();
};

#endif
