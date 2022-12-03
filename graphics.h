#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "viewer.h"
#include "window.h"

class Graphics: public Viewer {
        Xwindow *xw;
        // should maybe make this come from game instead??? - should be standard, shouldn't have to go around changing the basic board
        char curboard[rows][cols] = {{'r','n','b','q','k','b','n','r'}, {'p','p','p','p','p','p','p','p'}, {' ',' ',' ',' ',' ',' ',' ',' '}, {' ',' ',' ',' ',' ',' ',' ',' '}, {' ',' ',' ',' ',' ',' ',' ',' '}, {' ',' ',' ',' ',' ',' ',' ',' '}, {'P','P','P','P','P','P','P','P'}, {'R','N','B','Q','K','B','N','R'}};
        public:
        void update(char **board) override;//(char board[rows][cols]) override;
        Graphics(); //??????????????? or () and just initialise to standard beginning board? //or take in a char[][] of what the initial state should look like
        ~Graphics() override;
};
#endif
