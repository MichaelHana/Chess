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
	while (std::cin >> command) {
		switch(command) {
			case "game":
				//delete current board, players, viewers(??)? will this have - should actually just do this when game ends so players can't keep making moves on an already finished game
				board = new Board(start);
				for (int i=0; i<numplayers; ++i) {
					std::string player;
					std::cin >> player;
					switch(player1) {
						case "human":
							Human *plyr = new Human(std::cin);
							break;
						case "computer1":
							Computer1 *plyr = new Computer1(); // what arguments??
							break;
						case "computer2":
							Computer2 *plyr = new Computer2(); // what arguments??
							break;
						case "computer3":
							Computer3 *plyr = new Computer3(); // what arguments??
							break;
						case "computer4":
							Computer4 *plyr = new Computer4(); // what arguments??
							break;
						default:
							std::cout << invalid player: << player << std::endl;
					}
					players.emplace_back(plyr);
				}
				Text *text = new Text(); //parameters?? - make sure to send board layout, dimensions
				viewers.emplace_back(text);
				Graphics *graphic = new Graphic(); //parameters??
				viewers.emplace_back(graphic);
				break;
                        case "resign": //this would need to change if >2 players- basically just check turn mod numplayers
                                curplayer = turn%numplayers;
				for (int i=0; i<numplayers) {
					if (i!=curplayer) {
						wins[i]++;
					}
				}
				// effectively ends game - should delete all associated memory (board + players, maybe viewers?)
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


            
                
