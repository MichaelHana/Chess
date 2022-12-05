#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "viewer.h"
#include "window.h"
#include <memory>

class Graphics: public Viewer {
        std::unique_ptr<Xwindow> xw;
        // should maybe make this come from game instead??? - should be standard, shouldn't have to go around changing the basic board
        std::vector<std::vector<char>> curboard;//[rows][cols] = {{'r','n','b','q','k','b','n','r'}, {'p','p','p','p','p','p','p','p'}, {' ',' ',' ',' ',' ',' ',' ',' '}, {' ',' ',' ',' ',' ',' ',' ',' '}, {' ',' ',' ',' ',' ',' ',' ',' '}, {' ',' ',' ',' ',' ',' ',' ',' '}, {'P','P','P','P','P','P','P','P'}, {'R','N','B','Q','K','B','N','R'}};
	int last_x_start, last_y_start, last_x_end, last_y_end;
        public:
        void update(std::vector<std::vector<char>> board) override;//(char board[rows][cols]) override;
        Graphics(); //??????????????? or () and just initialise to standard beginning board? //or take in a char[][] of what the initial state should look like
        ~Graphics() override;
};
#endif
