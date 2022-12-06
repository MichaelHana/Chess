#ifndef MOVE_H
#define MOVE_H
#include <utility>

class Piece;

struct Move {
	std::pair<int, int> start;
	std::pair<int, int> end;
	std::pair<bool, char> capture;
	bool check;
	bool checkmate;
	bool castle;
	std::pair<bool, char> promote;
	bool enPassant;

	bool operator==(Move &other_move) {
		return other_move.start.first == other_move.end.first && other_move.start.second == other_move.end.second;
	}
};

#endif
