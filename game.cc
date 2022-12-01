#include "game.h"
#include "human.h"
#include "computer.h"
#include <string>
#include <iostream>

void Game::updateViewers() {
        char cur[rows][cols] = board.getState();
        for (Viewer *viewer: viewers) {
                viewer.update(cur);
        }
}
void Game::play() {
        std::string command;
                        while (std::cin >> command)
                                //delete current board, players, viewers(??)?
                                switch(command) {
                                        case "game":
                                                std::string player1;
                                                std::string player2;
                                                std::cin >> 
                                                board = new Board(start);
                                        /*for (int i=0; i<players;++i) {

                                        }*/ // should maybe see about changing implementation to allow for more players??
                                        switch(player1) {
                                                case "human":
                                                        Human *human = new Human();
                                                players.emplace_back(human);
                                                case "computer1":
                                                        Computer1 *computer = new Computer1(); // what arguments??
                                                        players.emplace_back(computer);
                                                case "computer2":
                                                        Computer2 *computer = new Computer2(); // what arguments??

                                                case "computer3":

                                                case "computer4":

                                                default:
                                                        //throw error to be caught in main?             
                                        }
                                        switch(black-player) {
                                                case "human":

                                                case "computer1":

                                                case "computer2":

                                                case "computer3":

                                                case "computer4":

                                                default:
                                                        //throw error to be caught in main? delete necessary memory to avoid leaks?
                                        }
                                        Text *text = new Text(); //parameters?? - make sure to send board layout, dimensions
                                        viewers.emplace_back(text);
                                        Graphics *graphic = new Graphic();//
                                        viewers.emplace_back(graphic);
                                
                        case "resign":
                                if (turn%2) {
                                        //return other player win
                                } else {
                                        //return other player win
                                }
                                break;
                        case "move":
                                if (turn%2) {
                                        board.listmoves(); // what type do I put this in?
                                        //get player move - what is the type I should take it as??
                                        // update board with move - checkmove??
                                        //call updateviewers with argument from board.getstate()
                                } else {
                                        //do same for other player
                                }
                                checkEnd();
                                break;
                        case "setup":
                                setup();
                                break;
                        default:
                                std::cout << command << " is not a valid command" << std::endl;
                }
        }
        // print final score, white wins and black wins
        // delete stuff? Or will it all be deleted in destructor?
}
void setup() {
        std::string command;
        switch(command) {
                case "+":

                case "-":

                case "=":

                case "done":
                        //check if board contains exactly one white king and one black king, no pawns are on the first or last row of the board, and neither king is in check - O.W. shouldn't leave setup mode, should output message to user
                        //if the conditions are met, should return to game setup, having made changes to board
                default:
                        std::cout << command << " is not a valid command, please enter one of [+ K e1], [- e1], [= colour] or [done]" << std::endl;
        }
}
int checkEnd() {
        
}


            
                
