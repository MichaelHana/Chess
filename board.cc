#include <vector>
#include <utility>
#include <memory>
#include "move.h"
#include "board.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
//#include "piece.h"

Board::Board(int row, int col, std::vector<std::vector<char>> board) : row{ row }, col{ col }, board { board } {
	for (int i = 0; i < row; ++i) {
		std::vector<std::unique_ptr<Piece>> piece_row;

		for (int j = 0; j < col; ++j) {
			if (board[j][i] >= 'a' && board[j][i] <= 'z') {
				if (board[j][i] == 'p') {
					piece_row.emplace_back(std::make_unique<Pawn>(1)); // black
				}
				else if (board[j][i] == 'r') {
					piece_row.emplace_back(std::make_unique<Rook>(1));
				}
				else if (board[j][i] == 'n') {
					piece_row.emplace_back(std::make_unique<Knight>(1));
				}
				else if (board[j][i] == 'b') {
					piece_row.emplace_back(std::make_unique<Bishop>(1));
				}
				else if (board[j][i] == 'q') {
					piece_row.emplace_back(std::make_unique<Queen>(1));
				}
				else {
					piece_row.emplace_back(std::make_unique<King>(1));
				}
			}
			else {
				if (board[j][i] == 'P') {
					piece_row.emplace_back(std::make_unique<Pawn>(0)); // white
				}
				else if (board[j][i] == 'R') {
					piece_row.emplace_back(std::make_unique<Rook>(0));
				}
				else if (board[j][i] == 'N') {
					piece_row.emplace_back(std::make_unique<Knight>(0));
				}
				else if (board[j][i] == 'B') {
					piece_row.emplace_back(std::make_unique<Bishop>(0));
				}
				else if (board[j][i] == 'Q') {
					piece_row.emplace_back(std::make_unique<Queen>(0));
				}
				else if (board[j][i] == 'K') {
					piece_row.emplace_back(std::make_unique<King>(0));
				}
			}
		}
		pieces.emplace_back(std::move(piece_row));
	}
}

bool Board::checkMove(Move m) {
	if (m.start.first >= 0 && m.start.second >= 0 && m.start.second <= pieces.size() && m.start.first <= pieces[m.start.second].size() && pieces[m.start.second][m.start.first] && pieces[m.start.second][m.start.first]->validMove(this, m.start, m.end)) {//check if piece can move there
		std::unique_ptr<Piece> captured_piece;
		//hang on to potentially captured piece
		if (pieces[m.end.second][m.end.first]) {
			captured_piece = std::move(pieces[m.end.second][m.end.first]);
		}
		//make the move
		pieces[m.end.second][m.end.first] = std::move(pieces[m.start.second][m.start.first]);
		pieces[m.start.first][m.start.second].reset();

		// revert move if king ends up in check
		if (check(pieces[m.start.second][m.start.first]->getColor())) {
			pieces[m.start.second][m.start.first] = std::move(pieces[m.end.second][m.end.first]);
			pieces[m.end.second][m.end.first] = std::move(captured_piece);
			return false;
		}
		return true;
	}
	return false;
}

std::vector<std::vector<char>> Board::getState() {
	return board;
}

Piece* Board::getPiece(std::pair<int, int> coords) {
	return pieces[coords.second][coords.first].get();
}

bool Board::check(int king_color) {
	//get king position
	int king_x = 0;
	int king_y = 0;
	for (int y = 0; y < pieces.size(); ++y) {
		for (int x = 0; x < pieces[i].size(); ++x) {
			Piece *king = dynamic_cast<King*>(pieces[y][x].get());
			if (king && pieces[y][x]->getColor() == king_color) {//piece is a king and matches the color of the moving piece
				king_x = x;
				king_y = y;
				break;
			}
		}
	}

	bool king_in_check = false;

	for (int y = 0; y < pieces.size(); ++y) {
		for (int x = 0; x < pieces[i].size(); ++x) {
			if (pieces[y][x] && pieces[y][x]->getColor() != pieces[king_y][king_x]->getColor()) {//piece is valid and color is opposite of the king's color
				std::pair<int, int> start_check = std::make_pair( x, y );
				std::pair<int, int> end_check = std::make_pair( king_x, king_y );
				if (pieces[y][x] && pieces[y][x]->validMove(this, start_check, end_check)) {
					king_in_check = true;
					break;
				}
			}
		}
	}

	return king_in_check;
}

int Board::checkmate(int color) {//0 = not checkmate or stalemate, 1 = checkmate, 2 = stalemate
	bool valid_moves = false;
	for (size_t i = 0; i < pieces.size(); ++i) {
		for (size_t j = 0; j < pieces[i].size(); ++j) {
			for (size_t y = 0; y < board.size(); ++y) {
				for (size_t x = 0; x < board[y].size(); ++x) {
					std::pair<int, int> start = std::make_pair( j, i );
					std::pair<int, int> end = std::make_pair( x, y );
					if (pieces[j][i] && pieces[j][i]->getColor() == color && pieces[j][i]->validMove(this, start, end)) {
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

std::vector<Move> Board::listMoves(int color) {
	std::vector<Move> moves;
	int opposite_color = 0;
	if (color == 0) {
		opposite_color = 1;
	}

	//loop through all pieces and through all squares and check for valid move
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			for (size_t y = 0; y < row; ++y) {
				for (size_t x = 0; x < col; ++x) {
					if (pieces[j][i]) {
						std::pair<int, int> start = std::make_pair( j, i );
						std::pair<int, int> end = std::make_pair( x, y );
						if (pieces[j][i]->validMove(this, start, end) && pieces[j][i]->getColor() == color) {
							bool is_capture = false, is_check = false, is_checkmate = false;
							if (pieces[end.second][end.first]) {
								is_capture = true;
							}
							is_check = check(opposite_color);//checking opposite colour piece
							if (checkmate(opposite_color) == 1) {
								is_checkmate = true;
							}
							Move m{ start, end, is_capture, is_check, is_checkmate };
							moves.emplace_back(m);
					
						}
					}
				}
			}
		}
	}

	return moves;
}

Board::~Board() {}
