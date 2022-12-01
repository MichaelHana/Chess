#include "symbols.h"
//include <string>

std::string convertpiece(char piece){
        switch (piece) {
                //might need to switch to also take a colour - should I create a colour enum somewhere?
                //might need to switch to a switch of characters representing pieces (k-king, q-queen, etc and maybe case insensitive?)
                // for colour, could just switch so that everything other than white is capital and add an extra colour parameter here and everywhere else where it's necessary
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
