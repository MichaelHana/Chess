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
				//reset turn to 0
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
							Level1 *plyr = new Level1(); // what arguments??
							break;
						case "computer2":
							Level2 *plyr = new Level2(); // what arguments??
							break;
						case "computer3":
							Level3 *plyr = new Level3(); // what arguments??
							break;
						case "computer4":
							Leve4 *plyr = new Level4(); // what arguments??
							break;
						default:
							std::cout << invalid player: << player << std::endl;
							// should this break and reset everything??
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
				curplayer = turn%numplayers;
                                //vector<Move *> validmoves = board.listmoves(); //ensure its not empty??
				std::pair<std::pair<int, int>, std::pair<int, int>> playermove = players[curplayer]->getMove(board.listmoves());
				board->move(playermove);
				updateViewers();
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
			//should maybe change order of players in players until the one we want is first?
                case "done":
                        //check if board contains exactly one white king and one black king, no pawns are on the first or last row of the board, and neither king is in check - O.W. shouldn't leave setup mode, should output message to user
                        //if the conditions are met, should return to game setup, having made changes to board
                default:
                        std::cout << command << " is not a valid command, please enter one of [+ K e1], [- e1], [= colour] or [done]" << std::endl;
        }
}
int checkEnd() {
        
}


            
                
