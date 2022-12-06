#ifndef TEXT_H
#define TEXT_H
#include <iostream>
#include "viewer.h"

class Text: public Viewer {
	std::ostream &out;
	public:
		Text(int rows, int cols, std::ostream &out);
		void update(std::vector<std::vector<char>> board) override;
		std::string convertpiece(char piece);
};
#endif
