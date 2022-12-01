#include <vector>
#include "move.h"
#include "board.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
//#include "piece.h"

//Piece** might not be correct and might have to change how to initialize the board

Board::Board(int row, int col, char** board) : row{ row }, col{ col }, board {board} {
	this->board = new char[col][row];
	pieces = new Player*[col][row];
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			this->board[j][i] = board[j][i];
			if (board[j][i] >= 'a' && board[j][i] <= 'z') {
				if (board[j][i] == 'p') {
					pieces[j][i] = new Pawn{ 1 }; // black
				}
				else if (board[j][i] == 'r') {
					pieces[j][i] = new Rook{ 1 };
				}
				else if (board[j][i] == 'n') {
					pieces[j][i] = new Knight{ 1 };
				}
				else if (board[j][i] == 'b') {
					pieces[j][i] = new Bishop{ 1 };
				}
				else if (board[j][i] == 'q') {
					pieces[j][i] = new Queen{ 1 };
				}
				else {
					pieces[j][i] = new King{ 1 };
				}
			else {
				if (board[j][i] == 'P') {
					pieces[j][i] = new Pawn{ 0 }; // white
				}
				else if (board[j][i] == 'R') {
					pieces[j][i] = new Rook{ 0 };
				}
				else if (board[j][i] == 'N') {
					pieces[j][i] = new Knight{ 0 };
				}
				else if (board[j][i] == 'B') {
					pieces[j][i] = new Bishop{ 0 };
				}
				else if (board[j][i] == 'Q') {
					pieces[j][i] = new Queen{ 0 };
				}
				else {
					pieces[j][i] = new King{ 0 };
				}
			}
		}
	}
}


bool Board::checkMove(Move m) {
	//rework this: pieces no longer return a type Move
	if (pieces[m.start.first][m.start.second]->validMove(this, m.start, m.end)) {//check if piece can move there
		Piece* captured_piece = nullptr;
		//hang on to potentially captured piece
		if (pieces[m.end.first][m.end.second]) {
			captured_piece = pieces[m.end.first][m.end.second];
		}
		//make the move
		pieces[m.end.first][m.end.second] = pieces[m.start.first][m.start.second];
		pieces[m.start.first][m.start.second] = nullptr;

		// revert move if king ends up in check
		if (check(piece[m.start.first][m.start.end]->getColor())) {
			piece[m.start.first][m.start.second] = piece[m.end.first][m.end.second];
			piece[m.end.first][m.end.second] = captured_piece;
			throw ("bad_move"); //might change
		}
	}
}

std::vector<std::vector<char>> getState() {
	return board;
}

bool check(int king_color) {
	//get king position
	int king_x = 0;
	int king_y = 0;
	for (int y = 0; y < row; ++y) {
		for (int x = 0; x < col; ++x) {
			Piece* king = dynamic_cast<King*>(piece[x][y]);
			if (king && piece[x][y]->getColor() == king_color) {//piece is a king and matches the color of the moving piece
				king_x = x;
				king_y = y;
				break;
			}
		}
	}

	bool king_in_check = false;

	for (int y = 0; y < row; ++y) {
		for (int x = 0; x < col; ++x) {
			if (piece[x][y] && piece[x][y]->getColor() != piece[king_x][king_y]->getColor()) {//piece is valid and color is opposite of the king's color
				std::pair<int, int> start_check = std::make_pair{ x, y };
				std::pair<int, int> end_check = std::make_pair{ king_x, king_y };
				if (pieces[x][y]->validMove(this, start_check, end_check)) {
					king_in_check = true;
					break;
				}
			}
		}
	}

	return king_in_check;
}

int checkmate(int color) {//0 = not checkmate or stalemate, 1 = checkmate, 2 = stalemate
	bool valid_moves = false;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			for (int y = 0; y < row; ++y) {
				for (int x = 0; x < col; ++x) {
					std::pair<int, int> start = std::make_pair{ j, i };
					std::pair<int, int> end = std::make_pair{ x, y };
					if (piece[j][i]->getColor() == color && piece[j][i]->validMove(this, start, end)) {
						valid_moves = true;
						break;
					}
				}
			}
		}
	}

	if (!valid_moves && check(color)) {
		return 1; // checkmate
	}
	else if (!valid_moves && !check(color)) {
		return 2; // stalemate
	}
	return 0; // game not ended
}

std::vector<Move> Board::listMoves(int colour) {
	std::vector<Move> moves;
	
	//loop through all pieces and through all squares and check for valid move
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			for (int y = 0; y < row; ++y) {
				for (int x = 0; x < col; ++x) {
					std::pair<int, int> start = std::make_pair{ j, i };
					std::pair<int, int> end = std::make_pair{ x, y };
					if (piece[j][i]->validMove(this, start, end)) {
						bool is_capture, is_check, is_checkmate;
						if (piece[end.first][end.second]) {
							capture = true;
						}
						is_check = check(!piece[j][i]->getColor());//checking opposite colour piece
						if (checkmate(!piece[j][i]->getColor()) == 1) {
							checkmate = true;
						}
						Move m{ start, end, is_capture, is_check, is_checkmate };
						moves.emplace_back(m);
					}
				}
			}
		}
	}

	return moves;
}

Board::~Board() {
	for (int i = 0; i < row; ++i) {
		delete []pieces[i];
	}
	delete []pieces;
}