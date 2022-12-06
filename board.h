#ifndef BOARD_H
#define BOARD_H
#include <utility>
#include <vector>
#include <memory>

struct Move;
struct Piece;

class Board {
	std::vector<std::vector<std::unique_ptr<Piece>>> pieces;
	std::vector<std::vector<char>> board;
	public:
		Board(int row, int col, std::vector<std::vector<char>> board);
		
		//determines valididty of move and plays it sometimes
		bool checkMove(Move m, int color, bool onlyTesting = false, char *capture = nullptr, bool *check_move = nullptr, bool *checkmate_move = nullptr, 
				bool *castle_move = nullptr, bool *is_promotion = nullptr, bool *is_enPassant = nullptr);
		
		std::vector<std::vector<char>> getState();//gets board
		Piece* getPiece(std::pair<int, int> coords);//gets piece at coords
		
		bool check(int king_color);//determines if king_color is in check
		int checkmate(int color);//determiens if color is in checkmate
		
		std::vector<Move> listMoves(int color);//determines all possible moves
		
		bool promote(Move m, int color);//promotes
		
		void place(char piece, std::pair<int, int> coord);//places piece at coord
		void remove(std::pair<int, int> coord);//removes piece at coord
		bool setupReady();//determines if board is ready to leave setup mode
		~Board();
};

#endif
