#include "text.h"
#include "symbols.h"
#include <iostream>

// need to ensure that will always be passed a 2d char array of the correct size (rows, cols) or this might seg fault?? - otherwise can change to determining rows and cols by size of board, then filling in board will blanks if its the wrong size??
void Text::update(char board[rows][cols]) {
        // could use black piece symbols with diff font colour for multiplayer

        //int rows = sizeof board / sizeof board[0];
        //int cols = sizeof board[0];
        for (int i=0; i<=3*cols; i++) {
                out << "-";
        }
        out << std::endl;
        for (int i=0; i<rows; i++) {
                out << "|";
                for (int j=0; j<cols;j++) {
                        std::string piece= convertpiece(board[i][j]);
                        if ((i+j)%2 && piece == " ") {
                                out << "__|";
                        } else {
                                out << piece << " |";
                        }
                }
                out << std::endl;
                for (int i=0; i<=3*cols; i++) {
                        out << "-";
                }
                out << std::endl;
        }
}

Text::Text(std::ostream &out): out(out) {}
