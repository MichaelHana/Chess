#include "text.h"
#include <iostream>

Text::Text(int rows, int cols, std::ostream &out): Viewer{rows, cols}, out(out) {}

void Text::update(std::vector<std::vector<char>> board) {

	//board top
        out << " ";
        for (int i=0; i <= 3 * cols; ++i) {
                out << "-";
        }

        out << std::endl;
        
	//print board
	for (int i = 0; i < rows; ++i) {
                out << i << "|";
                for (int j = 0; j < cols; ++j) {
                        std::string piece = convertpiece(board[i][j]);
                        if ((i+j)%2 && piece == " ") {
                                out << "\u25A0 |";
                        } else {
                                out << piece << " |";
                        }
                }
                out << std::endl;
                out << " ";
                for (int i = 0; i <= 3 * cols; ++i) {
                        out << "-";
                }
                out << std::endl;
        }
        for (int k=0; k < cols; ++k) {
                char letter = 'a'+k;
                std::string strletter(1,letter);
                out << "  " << strletter;
        }
        out << std::endl;
}

std::string Text::convertpiece(char piece){
        switch (piece) {
                // white: //IMPORTANT: on dark mode, these look opposite!!!
                case 'k': return "\u2654";
                case 'q': return "\u2655";
                case 'r': return "\u2656";
                case 'b': return "\u2657";
                case 'n': return "\u2658"; //knight
                case 'p': return "\u2659";
                // black:
                case 'K': return "\u265A";
                case 'Q': return "\u265B";
                case 'R': return "\u265C";
                case 'B': return "\u265D";
                case 'N': return "\u265E";
                case 'P': return "\u265F";
                default: return " ";
        }
}
