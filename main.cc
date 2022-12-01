#include <string>
#include <iostream>
#include "game.h"

int main() {
        int whitewins;
        int blackwins;
        std::string command;
        while (std::cin >> command) {
                switch(command) {
                        case "game":
                                Game *game = new Game(); // parameters?
                                //call game to start
                                //should get a result back - change value of whitewins or blackwins (or both by half in case of tie)
                                //delete game
                        default:
                                std::cout << command << " is not a valid command" << std::endl;
                }
        }
        // print final score, white wins and black wins

}
