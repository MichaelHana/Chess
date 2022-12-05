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

bool Board::checkMove(Move m, bool onlyTesting) {
	int pieces_size = static_cast<int>(pieces.size());
	if (m.start.second < pieces_size && m.end.second < pieces_size) {
		int pieces_start_size = static_cast<int>(pieces[m.start.second].size());
		int pieces_end_size = static_cast<int>(pieces[m.end.second].size());
		/*std::cout << "here0" << std::endl;
		/*std::cout << "pieces_start_size" << pieces_start_size << std::endl;
		std::cout << "pieces_end_size" << pieces_end_size << std::endl;
		std::cout << "m.satrt.first: " << m.start.first << std::endl;
		std::cout << "m.start.second:  " << m.start.second << std::endl;
		std::cout << "m.end.first: " << m.end.first << std::endl;
		std::cout << "m.end.second: " << m.end.second << std::endl;
		if (pieces[m.start.second][m.start.first].get()) {
			std::cout << "1 works" << std::endl;
		
			std::cout << m.start.first << m.start.second << m.end.first << m.end.second << std::endl;
			if (pieces[m.start.second][m.start.first]->validMove(this, m.start, m.end)) {
				std::cout << "2 works" << std::endl;
			}
		}*/

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
			if (pieces[y][x] && pieces[y][x]->getColor() != pieces[king_y][king_x]->getColor()) {//piece is valid and color is opposite of the king's color
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
	for (size_t i = 0; i < pieces.size(); ++i) {
		for (size_t j = 0; j < pieces[i].size(); ++j) {
			for (size_t y = 0; y < board.size(); ++y) {
				for (size_t x = 0; x < board[y].size(); ++x) {
					std::pair<int, int> start = std::make_pair( j, i );
					std::pair<int, int> end = std::make_pair( x, y );
					if (pieces[i][j].get() && pieces[i][j]->getColor() == color && checkMove({start, end, false, false, false}, true)) {
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
	for (size_t i = 0; i < pieces.size(); ++i) {
		for (size_t j = 0; j < pieces[i].size(); ++j) {
			for (size_t y = 0; y < board.size(); ++y) {
				for (size_t x = 0; x < board[y].size(); ++x) {
					if (pieces[i][j]) {
						std::pair<int, int> start = std::make_pair( j, i );
						std::pair<int, int> end = std::make_pair( x, y );
						//std::cout << " listMoves: endx: " << end.first << " endy: " << end.second << std::endl;
						//std::cout << " listmoves startx: " << j << " starty: " << i << std::endl;
						if (checkMove({start, end, false, false, false}, true) && pieces[i][j]->getColor() == color) {
							//std::cout << " valid " << std::endl;
							//std::cout << "valid " << std::endl;
							//std::cout << " listmoves startx: " << j << " starty: " << i << std::endl;
							
							bool is_capture = false, is_check = false, is_checkmate = false;
							std::unique_ptr<Piece> captured_piece;
							
							if (pieces[end.second][end.first]) {
								is_capture = true;
								captured_piece = std::move(pieces[end.second][end.first]);
							}	

							is_check = check(opposite_color);//checking opposite colour piece
							if (checkmate(opposite_color) == 1) {
								is_checkmate = true;
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

Board::~Board() {}
