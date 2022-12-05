#include <vector>
#include <iostream>
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
#include "piece.h"

Board::Board(int row, int col, std::vector<std::vector<char>> board) : row{ row }, col{ col }, board { board } {
	for (int i = 0; i < col; ++i) {
		std::vector<std::unique_ptr<Piece>> piece_row;

		for (int j = 0; j < row; ++j) {
			char c = board[i][j];
			if (c >= 'a' && c <= 'z') {
				if (c == 'p') {
					piece_row.emplace_back(std::make_unique<Pawn>(1)); // black
				}
				else if (c == 'r') {
					piece_row.emplace_back(std::make_unique<Rook>(1));
				}
				else if (c == 'n') {
					piece_row.emplace_back(std::make_unique<Knight>(1));
				}
				else if (c == 'b') {
					piece_row.emplace_back(std::make_unique<Bishop>(1));
				}
				else if (c == 'q') {
					piece_row.emplace_back(std::make_unique<Queen>(1));
				}
				else {
					piece_row.emplace_back(std::make_unique<King>(1));
				}
			}
			else if (c >= 'A' && c <= 'Z') {
				if (c == 'P') {
					piece_row.emplace_back(std::make_unique<Pawn>(0)); // white
				}
				else if (c == 'R') {
					piece_row.emplace_back(std::make_unique<Rook>(0));
				}
				else if (c == 'N') {
					piece_row.emplace_back(std::make_unique<Knight>(0));
				}
				else if (c == 'B') {
					piece_row.emplace_back(std::make_unique<Bishop>(0));
				}
				else if (c == 'Q') {
					piece_row.emplace_back(std::make_unique<Queen>(0));
				}
				else if (c == 'K') {
					piece_row.emplace_back(std::make_unique<King>(0));
				}
			}
			else {
				auto p = std::make_unique<Pawn>(-1);
				p.reset();
				piece_row.emplace_back(std::move(p));
			}
		}
		pieces.emplace_back(std::move(piece_row));
	}
}

bool Board::checkMove(Move m, bool onlyTesting, bool *check_move, bool *checkmate_move) {
	int pieces_size = static_cast<int>(pieces.size());
	if (m.start.second < pieces_size && m.end.second < pieces_size) {
		int pieces_start_size = static_cast<int>(pieces[m.start.second].size());
		int pieces_end_size = static_cast<int>(pieces[m.end.second].size());
		if (m.start.first >= 0 && m.start.second >= 0  && m.start.first < pieces_start_size && m.end.first >= 0 && m.end.second >= 0 && m.end.first < pieces_end_size && pieces[m.start.second][m.start.first] && pieces[m.start.second][m.start.first]->validMove(this, m.start, m.end)) {//check if piece can move there
			std::unique_ptr<Piece> captured_piece;
			
			//hang on to potentially captured piece
			if (pieces[m.end.second][m.end.first].get()) {
				captured_piece = std::move(pieces[m.end.second][m.end.first]);
			}

			//make the move
			pieces[m.end.second][m.end.first] = std::move(pieces[m.start.second][m.start.first]);
			pieces[m.start.second][m.start.first].reset();
			// revert move if king ends up in check
			if (check(pieces[m.end.second][m.end.first]->getColor())) {
				pieces[m.start.second][m.start.first] = std::move(pieces[m.end.second][m.end.first]);
				pieces[m.end.second][m.end.first] = std::move(captured_piece);
				return false;
			}

			//return if move is a check or checkmate
			int opposite_color = 0;
			if (pieces[m.end.second][m.end.first]->getColor() == 0) {
				opposite_color = 1;
			}

			if (check_move) {
				if (check(opposite_color)) {
					*check_move = true;
				}
			}

			if (checkmate_move) {
				if (checkmate(opposite_color)) {
					*checkmate_move = true;
				}
			}

			if (!onlyTesting) {
				// update board and commit to move
				board[m.end.second][m.end.first] = board[m.start.second][m.start.first];
				board[m.start.second][m.start.first] = ' ';
				pieces[m.end.second][m.end.first]->setMoved();
			} else {
				//undo the move
				pieces[m.start.second][m.start.first] = std::move(pieces[m.end.second][m.end.first]);
				pieces[m.end.second][m.end.first] = std::move(captured_piece);
			}
			return true;
		}
		return false;
	}
	return false;
}

std::vector<std::vector<char>> Board::getState() {
	return board;
}

Piece* Board::getPiece(std::pair<int, int> coords) {
	if (coords.first >= 0 && coords.second >= 0 && coords.second < static_cast<int>(pieces.size()) && coords.first < static_cast<int>(pieces[coords.second].size()) && pieces[coords.second][coords.first].get()) {
		return pieces[coords.second][coords.first].get();
	}

	return nullptr;
}

bool Board::check(int king_color) {
	//get king position
	int king_x = 0;
	int king_y = 0;
	for (int y = 0; y < static_cast<int>(pieces.size()); ++y) {
		for (int x = 0; x < static_cast<int>(pieces[y].size()); ++x) {
			Piece *king = dynamic_cast<King*>(pieces[y][x].get());
			if (king && pieces[y][x]->getColor() == king_color) {//piece is a king and matches the color of the moving piece
				king_x = x;
				king_y = y;
				break;
			}
		}
	}

	for (int y = 0; y < static_cast<int>(pieces.size()); ++y) {
		for (int x = 0; x < static_cast<int>(pieces[y].size()); ++x) {
			if (pieces[y][x] && pieces[y][x]->getColor() != king_color) {//piece is valid and color is opposite of the king's color
				std::pair<int, int> start_check = std::make_pair( x, y );
				std::pair<int, int> end_check = std::make_pair( king_x, king_y );
				if (pieces[y][x] && pieces[y][x]->validMove(this, start_check, end_check)) {
					return true;
				}
			}
		}
	}

	return false;
}

int Board::checkmate(int color) {//0 = not checkmate or stalemate, 1 = checkmate, 2 = stalemate
	bool valid_moves = false;
	int piece_count = 0;
	for (size_t i = 0; i < pieces.size(); ++i) {
		for (size_t j = 0; j < pieces[i].size(); ++j) {
			if (pieces[i][j].get()) {
				++piece_count;
				for (size_t y = 0; y < board.size(); ++y) {
					for (size_t x = 0; x < board[y].size(); ++x) {
						std::pair<int, int> start = std::make_pair( j, i );
						std::pair<int, int> end = std::make_pair( x, y );
					       	if (pieces[i][j]->getColor() == color && checkMove({start, end, false, false, false}, true)) {
							valid_moves = true;
							break;
						}
					}
				}
			}
		}
	}
	if (!valid_moves && check(color)) {
		return 1; // checkmate
	}
	else if ((!valid_moves && !check(color)) || piece_count <= 2) {
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
	for (size_t i = 0; i < pieces.size(); ++i) {
		for (size_t j = 0; j < pieces[i].size(); ++j) {
			for (size_t y = 0; y < board.size(); ++y) {
				for (size_t x = 0; x < board[y].size(); ++x) {
					if (pieces[i][j]) {
						std::pair<int, int> start = std::make_pair( j, i );
						std::pair<int, int> end = std::make_pair( x, y );
						bool is_capture = false, is_check = false, is_checkmate = false;
						if (checkMove({start, end, false, false, false}, true, &is_check, &is_checkmate) && pieces[i][j]->getColor() == color) {
							if (pieces[end.second][end.first]) {
								is_capture = true;
							}	

							Move m { start, end, is_capture, is_check, is_checkmate };
							moves.emplace_back(m);
						}
					}
				}
			}
		}
	}

	return moves;
}

void Board::place(char piece, std::pair<int, int> coord) {
	if (coord.first >= 0 && coord.second >= 0 && coord.second < static_cast<int>(pieces.size()) && coord.first < static_cast<int>(pieces[coord.second].size())) {
		if (pieces[coord.second][coord.first]) {
			std::cout << "You cannot place a piece there." << std::endl;
		} else {
			if (piece >= 'a' && piece <= 'z') {
				if (piece == 'p') {
					pieces[coord.second][coord.first] = std::make_unique<Pawn>(1); // black
				}
				else if (piece == 'r') {
					pieces[coord.second][coord.first] = std::make_unique<Rook>(1);
				}
				else if (piece == 'n') {
					pieces[coord.second][coord.first] = std::make_unique<Knight>(1);
				}
				else if (piece == 'b') {
					pieces[coord.second][coord.first] = std::make_unique<Bishop>(1);
				}
				else if (piece == 'q') {
					pieces[coord.second][coord.first] = std::make_unique<Queen>(1);
				}
				else if (piece == 'k') {
					pieces[coord.second][coord.first] = std::make_unique<King>(1);
				}
			}

			else if (piece >= 'A' && piece <= 'Z') {
				if (piece == 'P') {
					pieces[coord.second][coord.first] = std::make_unique<Pawn>(0); // white
				}
				else if (piece == 'R') {
					pieces[coord.second][coord.first] = std::make_unique<Rook>(0);
				}
				else if (piece == 'N') {
					pieces[coord.second][coord.first] = std::make_unique<Knight>(0);
				}
				else if (piece == 'B') {
					pieces[coord.second][coord.first] = std::make_unique<Bishop>(0);
				}
				else if (piece == 'Q') {
					pieces[coord.second][coord.first] = std::make_unique<Queen>(0);
				}
				else if (piece == 'K') {
					pieces[coord.second][coord.first] = std::make_unique<King>(0);
				}
			}
			board[coord.second][coord.first] = piece;
		}
	} else {
		std::string error = "Invalid coordinate.";
		throw (error);
	}
}

void Board::remove(std::pair<int, int> coord){
	if (coord.first >= 0 && coord.second >= 0 && coord.second < static_cast<int>(pieces.size()) && coord.first < static_cast<int>(pieces[coord.second].size())) {
		pieces[coord.second][coord.first].reset();
		board[coord.second][coord.first] = ' ';
	} else {
		std::string error = "Invalid coordinate.";
		throw (error);
	}
}

bool Board::setupReady() {
	int king_count = 0;
	bool white_king = false, black_king = false;
	for (size_t i = 0; i < pieces.size(); ++i) {
		for (size_t j = 0; j < pieces[i].size(); ++j) {
			if (dynamic_cast<King *>(pieces[i][j].get())) {
				++king_count;
				if (king_count > 2) {
					return false;
				}
				if (pieces[i][j]->getColor() == 0) {
					white_king = true;
				} else if (pieces[i][j]->getColor() == 1) {
					black_king = true;
				}
			} else if (dynamic_cast<Pawn *>(pieces[i][j].get())) {
				if (i == 0 || i == 7) {
					return false;
				}
			}
		}
	}
	return white_king && black_king && !check(0) && !check(1);
}


Board::~Board() {}
