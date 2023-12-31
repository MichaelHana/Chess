#include <iostream>
#include <vector>
#include "human.h"
#include "move.h"

Human::Human(int color, std::istream& in) : Player{ color } , in{ in } {}

Move Human::getMove(std::vector<Move> moves) {
	std::string start, end;
	in >> start >> end;
	
	//make sure input coords are valid
	if (start.size() != 2) {
		throw (start.size());
	}

	if (end.size() != 2) {
		throw (end.size());
	}

	//convert coords to program langauage
	int start_x, start_y, end_x, end_y;
	start_x = start[0] - 'a';
	start_y = 8 - (start[1] - '0');
	end_x = end[0] - 'a';
	end_y = 8 - (end[1] - '0');

	//convert values to coord pairs
	std::pair<int, int> start_move = std::make_pair( start_x, start_y );
	std::pair<int, int> end_move = std::make_pair( end_x, end_y );

	Move m {start_move, end_move};
	return m;
}

char Human::getPromotion() {
	//get promotion char
	char c;
	in >> c;
	return c;
}
