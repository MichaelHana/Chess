#include <cstdlib>
#include <ctime>
#include <vector>
#include "level2.h"
#include "move.h"
#include <iostream>
Level2::Level2(int color) : Computer{ color } {};

Move Level2::getMove(std::vector<Move> moves) {
	srand(time(nullptr));
	
	std::vector<Move> filter;
	
	for (auto i: moves) {
		if (i.check || i.capture || i.checkmate) {
			filter.emplace_back(i);
		}
	}

	if (filter.size() > 0) {
		int random = rand() % filter.size();
		std::cout << "check: " << filter[random].check << std::endl;
		return filter[random];
	}

	int random = rand() % moves.size();
	return moves[random];
}
