#include <iostream>
#include <vector>
#include "human.h"
#include "move.h"

Human::Human(int color, std::istream& in) : in{ in }, Player{ color } {}

Move Human::getMove(std::vector<Move> moves) {
	std::string start, end;
	in >> start >> end;
	
	if (start.size() > 2) {
		throw (start.size());
	}

	if (end.size() > 2) {
		throw (end.size());
	}

	int start_x, start_y, end_x, end_y;
	start_x = start[0] - 'a';
	start_y = start[1] - '0';
	end_x = end[0] - 'a';
	end_y = end[1] - '0';

	std::pair<int, int> start_move = std::make_pair( start_x, start_y );
	std::pair<int, int> end_move = std::make_pair( end_x, end_y );

	int i = 0;
	for (; i < moves.size(); ++i) {
		if (start_move == moves[i].start && end_move == moves[i].end) {
			break;
		}
	}

	return moves[i];
}