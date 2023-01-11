#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include "game.h"
#include "board.h"
#include "pawn.h"
#include "human.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "text.h"
#include "graphics.h"
#include "move.h"
#include "moveerror.h"

const std::vector<std::vector<char>> regular_setup =  { {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, 
							{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, 
							{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
							{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
							{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
							{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
							{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, 
							{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
	

void Game::updateViewers()
{
	//updates viewers
	std::vector<std::vector<char>> cur = board->getState();
	for (auto viewer = viewers.begin(); viewer != viewers.end(); ++viewer) {
		viewer->get()->update(cur);
	}
}

void Game::play()
{

	//original setup
	start = regular_setup;
	board = std::make_unique<Board>(rows, cols, start);

	std::string command;

	viewers.emplace_back(std::make_unique<Text>(rows, cols, std::cout));
	viewers.emplace_back(std::make_unique<Graphics>(rows, cols));

	//main loop
	while (std::cin >> command){
		if (command == "game") {
			if (game_running) {
				std::cout << "there is already a game running" << std::endl;
				continue;
			}

			bool valid_inputs = true;
				
			for (int i = 0; i < numplayers; ++i) {
				std::string player;
				std::cin >> player;
				if (player == "human") {
					players.emplace_back(std::make_unique<Human>(i, std::cin));
				} else if (player == "computer1") {
					players.emplace_back(std::make_unique<Level1>(i));
				} else if (player == "computer2") {
					players.emplace_back(std::make_unique<Level2>(i));
				} else if (player == "computer3") {
					players.emplace_back(std::make_unique<Level3>(i));
				} else if (player == "computer4") {
					players.emplace_back(std::make_unique<Level4>(i));
				} else {
					std::cout << "invalid player :" << player << std::endl;
					
					//get rid of players you added since the rest was invalid
					for (size_t j = 0; j < players.size(); ++j) {
						players.pop_back();
					}

					valid_inputs = false;
					game_running = false;
					break; // break to reset input
				}
			}

			if (valid_inputs) {
				game_running = true;
				board = std::make_unique<Board>(rows, cols, start);
				updateViewers();
			}
		} 
		
		else if (command == "resign") {
			if (!game_running)
			{
				std::cout << "The game has ended. Please start a new game before resigning." << std::endl;
				continue;
			}

			int curplayer = turn % numplayers;
			for (int i = 0; i < numplayers; ++i) {
				if (i != curplayer)
				{
					wins[i]++;
				}
			}

			if (curplayer == 0) {
				std::cout << "Black Wins!" << std::endl;
			} else if (curplayer == 1) {
				std::cout << "White Wins!" << std::endl;
			}

			//reseting play
			turn = 0;
			game_running = false;
			start = regular_setup;

			for (int i = 0; i < numplayers; ++i) {
				players.pop_back();
			}

			move_history.clear();
		}
		
		else if (command == "move") {
			if (!game_running) {
				std::cout << "The game has ended. Please start a new game before making moves." << std::endl;
				continue;
			}

			int curplayer = turn % numplayers;
			bool valid_move = false;

			//get possible moves
			std::vector<Move> moves = board->listMoves(players[curplayer]->getColor());

			if (moves.size() > 0) {
				Move playermove = players[curplayer]->getMove(moves);
				
				//check for promotion
				if (board->promote(playermove, curplayer)) {
					playermove.promote.first = true;
					char c = players[curplayer]->getPromotion();
					playermove.promote.second = c;
				}
				
				//check for move validity
				valid_move = board->checkMove(playermove, curplayer);
				
				if (valid_move) {
					move_history.emplace_back(playermove);
				}
				
				updateViewers();
			}

			if (valid_move) {
				checkEnd();
				turn++;

				//update enpassants
				int move_history_size = static_cast<int>(move_history.size());
				int second_last = move_history_size - 2;
				if (move_history_size > 1 && abs(move_history[second_last].end.second - move_history[second_last].start.second) == 2 && 
						abs(move_history[second_last].end.first - move_history[second_last].start.first) == 0) {//if enPassant
					Pawn *pawn = dynamic_cast<Pawn *>(board->getPiece(move_history[second_last].end));
					if (pawn) {
						pawn->setEnPassant(false);	
					}
				}
			} else {
				std::cout << "Invalid move. Please enter a valid move" << std::endl;
			}
		}

		else if (command == "setup") {
			setup();
		}

		else if (command == "undo") {
			if (static_cast<int>(move_history.size()) <= 0) {//no move has been played
				std::cout << "Cannot undo." << std::endl;
				continue;
			}

			std::vector<std::vector<char>> board_copy = board->getState();
			Move last_move = move_history.back();
			
			//undo enpassant
			if (last_move.enPassant) {
				if (last_move.end.second < last_move.start.second) {//white
					board->place('p', std::make_pair(last_move.end.first, last_move.start.second));
				} else if (last_move.end.second > last_move.start.second) {//black
					board->place('P', std::make_pair(last_move.end.first, last_move.start.second));
				}
			}
			
			//undo regular move
			try {
				board->place(board_copy[last_move.end.second][last_move.end.first], last_move.start);
				board->remove(last_move.end);
				if (last_move.capture.first && !last_move.enPassant) {
					board->place(last_move.capture.second, last_move.end);
				}
			} catch (MoveError e) {
				std::cout << e.what() << std::endl;
			}

			//undo castle
			if (last_move.castle) {
				int direction = last_move.end.first - last_move.start.first;
				int rook_index = 5;
				int rook_original = 7;

				if (direction < 0) {//deciding which rook
					rook_index = 3;
					rook_original = 0;
				}
					
				try {
					board->place(board_copy[last_move.start.second][rook_index], std::make_pair(rook_original, last_move.start.second));
					board->remove(std::make_pair(rook_index, last_move.start.second));
					if (last_move.capture.first && !last_move.enPassant) {
						board->place(last_move.capture.second, last_move.end);
					}
				}  catch (MoveError e) {
					std::cout << e.what() << std::endl;
				}
			}

			//undo promotion
			if (last_move.promote.first) {
				try {
					board->remove(last_move.start);
					if (board_copy[last_move.end.second][last_move.end.first] >= 'A' && board_copy[last_move.end.second][last_move.end.first] <= 'Z') {// white
						board->place('P', last_move.start);
					} else if (board_copy[last_move.end.second][last_move.end.first] >= 'a' && board_copy[last_move.end.second][last_move.end.first] <= 'z') {//black
						board->place('p', last_move.start);
					}
				} catch (MoveError e) {
					std::cout << e.what() << std::endl;
				}
			}
		
			--turn;
			move_history.pop_back();	
			updateViewers();
		}

		else {
			std::cout << command << " is not a valid command" << std::endl;
		}
	}

	// print final score, white wins and black wins
	std::cout << "Final Score:" << std::endl;
	std::cout << "White: " << wins[0] << std::endl;
	std::cout << "Black: " << wins[1] << std::endl;
}

void Game::setup() {
	//creating empty board
	std::vector<std::vector<char>> empty_board; 
	for (int i = 0; i < rows; ++i) {
		std::vector<char> board_row;
		for (int j = 0; j < cols; ++j) {
			board_row.emplace_back(' ');
		}
		empty_board.emplace_back(board_row);
	}
			
	board = std::make_unique<Board>(rows, cols, empty_board);

	updateViewers();

	std::string command;
	while (std::cin >> command) {//setup mode command loop
		if (command == "+") {
			char c;
			std::string coord;
			std::cin >> c >> coord;
			
			//if not valid coord
			if (coord.size() != 2) {
				std::cout << "Invalid Coordinate." << std::endl;
				continue;
			}

			//convert coord to pair
			std::pair<int, int> coord_pair = std::make_pair(coord[0] - 'a', 8 - (coord[1] - '0'));
			
			//place piece
			try {
				board->place(c, coord_pair); 
			} catch (MoveError e) {
				std::cout << e.what() << std::endl;
			}
		} else if (command == "-") {
			std::string coord;
			std::cin >> coord;

			//if not valid coord
			if (coord.size() != 2) {
				std::cout << "Invalid Coordinate." << std::endl;
				continue;
			}
			
			//convert coord to pair
			std::pair<int, int> coord_pair = std::make_pair(coord[0] - 'a', 8 - (coord[1] - '0'));
			
			//remove piece
			try {
				board->remove(coord_pair); 
			} catch (MoveError e) {
				std::cout << e.what() << std::endl;
			}
		} else if (command == "=") {
			std::string color;
			std::cin >> color;

			//convert string to lowercase
			int size = static_cast<int>(color.size());
			for (int i = 0; i < size; ++i) {
				if (color[i] >= 'A' && color[i] <= 'Z') {
					color[i] += 'a' - 'A';
				}
			}

			if (color == "white") {
				turn = 0;
			} else if (color == "black") {
				turn = 1;
			} else {
				std::cout << "Invalid Color." << std::endl;
				continue;
			}
		} else if (command == "done") {
			if (board->setupReady()) {//check if board is ready to leave setup
				start = board->getState();
				return;
			} else {
				std::cout << "You cannot leave setup mode until there are no pawns on the first and last rows, there are only 2 kings, and neither king is in check." 
					<< std::endl;
			}
		} else {
			std::cout << command << " is not a valid command, please enter one of [+ K e1], [- e1], [= colour] or [done]" << std::endl;
		}

		updateViewers();
	}
}

void Game::checkEnd() {
	bool end = false;

	//get current player and next player
	int curplayer = turn % numplayers;
	int nextplayer = curplayer + 1;
	if (nextplayer >= numplayers) {
		nextplayer = 0;
	}

	//get game state
	int state = board->checkmate(players[nextplayer]->getColor());
	
	if (state == 0) {//game not ended
		if (board->check(0)) {//white in check
			std::cout << "White is in check." << std::endl;
		} else if (board->check(1)) {//black in check
			std::cout << "Black is in check." << std::endl;
		}
	} else if (state == 1) {//checkmate
		end = true;
		wins[curplayer]++;//update winner score
		if (curplayer == 0) {
			std::cout << "White wins!" << std::endl;
		} else {
			std::cout << "Black wins!" << std::endl;
		}
	} else if (state == 2) { // stalemate
		end = true;

		//update every player's score
		for (int j = 0; j < numplayers; ++j)
		{
			wins[j] += 0.5;
		}

		std::cout << "Stalemate!" << std::endl;
	}

	if (end) {//game has ended
		//reset everything	
		turn = 0;
		game_running = false;
		start = regular_setup;

		//reset players
		for (int i = 0; i < numplayers; ++i) {
			players.pop_back();
		}

		move_history.clear();
	}
}
Game::~Game() {}
