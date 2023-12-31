#include <cstdlib>
#include <vector>
#include <ctime>
#include "level4.h"
#include "move.h"

Level4::Level4(int color) : Computer{ color } {};

Move Level4::getMove(std::vector<Move> moves) {
	srand(time(nullptr));
	
	std::vector<Move> checkmates;
	std::vector<Move> checks;
	std::vector<Move> captures;
	std::vector<Move> castles;
	std::vector<Move> promotions;

	//filter checks, checkmates, captures, castles, and promotions
	for (auto i : moves) {
		if (i.checkmate) {
			checkmates.emplace_back(i);
		}
		if (i.check) {
			checks.emplace_back(i);
		}
		if (i.capture.first) {
			captures.emplace_back(i);
		}
		if (i.castle) {
			castles.emplace_back(i);
		}
		if (i.promote.first) {
			promotions.emplace_back(i);
		}
	}

	//if can checkmate, then checkmate
	if (static_cast<int>(checkmates.size()) > 0) {
		return checkmates[0];
	}

	//finding best move
	std::vector<Move> filter;

	//filter captures
	if (static_cast<int>(captures.size()) > 0) {
		char highest_char = ' ';
		for (auto i : captures) {//filter capturing moves and pick the highest piece to capture
			if (i.capture.second == 'Q' || i.capture.second == 'q') {
				highest_char = 'q';
			} else if (i.capture.second == 'R' || i.capture.second == 'r') {
				if (highest_char != 'q') {
					highest_char = 'r';
				}
			} else if (i.capture.second == 'B' || i.capture.second == 'b' || i.capture.second == 'K' || i.capture.second == 'k') {
				if (highest_char != 'q' && highest_char != 'r') {
					highest_char = 'b';
				}
			} else {
				highest_char = 'p';
			}
		}
		
		//add captures to filter
		for (auto i : captures) {
			if (i.capture.second == highest_char || i.capture.second == highest_char - 'a' + 'A') {
				filter.emplace_back(i);
			}
		}
		
	}

	//filter checks
	if (static_cast<int>(checks.size()) > 0) {
		std::vector<Move> temp;	

		//check if any of the filtered moves are checks
		for (auto i = filter.begin(); i != filter.end(); ++i) {
			for (auto j = checks.begin(); j != checks.end(); ++j) {
				if (i->start.first != j->start.first || i->start.second != j->start.second || i->end.first != j->end.second || i->end.second != j->end.second) { 
					temp.emplace_back(*i);;
				}
			}
		}
	
		//if there are no checks that are captures, then filter is only checks
		if (static_cast<int>(filter.size()) == 0) {
			filter = checks;
		}

		//captures become captures with check
		if (static_cast<int>(temp.size()) > 0) {
			filter = temp;
		}
	}

	//filter promotions
	if (static_cast<int>(promotions.size() > 0)) {
		std::vector<Move> temp;
		
		//check if any of the filtered movess are promotions
		for (auto i = filter.begin(); i != filter.end(); ++i) {
			for (auto j = promotions.begin(); j != promotions.end(); ++j) {
				if (i->start.first != j->start.first || i->start.second != j->start.second || i->end.first != j->end.second || i->end.second != j->end.second) { 
					temp.emplace_back(*i);
				}
			}
		}
	
		//if there are no checks or captures, then filter is only promotions
		if (static_cast<int>(filter.size()) == 0) {
			filter = promotions;
		}
	
		//moves are now a combination of captures, checks, and promotions
		if (static_cast<int>(temp.size()) > 0) {
			filter = temp;
		}
	}		

	//castle filter
	if (static_cast<int>(castles.size()) > 0) {
		std::vector<Move> temp;
		
		//check if any of the filtered moves are castles
		for (auto i = filter.begin(); i != filter.end(); ++i) {
			for (auto j = promotions.begin(); j != promotions.end(); ++j) {
				if (i->start.first != j->start.first || i->start.second != j->start.second || i->end.first != j->end.second || i->end.second != j->end.second) { 
					temp.emplace_back(*i);
				}
			}
		}
	
		//if there are no checks, captures, or promotions, then filter is only castles
		if (static_cast<int>(filter.size()) == 0) {
			filter = castles;
		}

		//moves are now a combination of captures, checks, promotions, and castles
		if (static_cast<int>(temp.size()) > 0) {
			filter = temp;
		}
	}

	//pick a move from filtered options
	if (filter.size() > 0) {
		int random = rand() % filter.size();
		return filter[random];
	}

	int random = rand() % moves.size();
	return moves[random];
}

char Level4::getPromotion() {
	//promotes always to a queen
	if (color == 0) {
		return 'Q';
	} else if (color == 1) {
		return 'q';
	}
	return ' ';
}
