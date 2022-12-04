#include "game.h"
#include "board.h"
#include "human.h"
#include "computer.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
// include "level4.h"
#include "text.h"
// include "graphics.h"
#include "move.h"
#include <string>
#include <iostream>
#include <memory>
#include <vector>

void Game::updateViewers()
{
	std::vector<std::vector<char>> cur = board->getState(); //had cur[rows][cols]
	for (auto viewer = viewers.begin(); viewer != viewers.end(); ++viewer) {
		viewer->get()->update(cur);
	}
}

void Game::play()
{
	// This is fine - if wanted to change layout, would need to implemenet new viewer and Text constructors to take in rows and cols
	// Graphics *graphic = new Graphic(); // This is fine - if wanted to change layout etc, would need to implement new viewer and graphics ctors, would just add parameters rows, columns, start

	std::string command;
	while (std::cin >> command)
	{
		if (command == "game")
		{
			game_running = true;
			start = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
			board = std::make_unique<Board>(rows, cols, start);
			for (int i = 0; i < numplayers; ++i)
			{
				std::string player;
				std::cin >> player;
				if (player == "human")
				{
					players.emplace_back(std::make_unique<Human>(i, std::cin));
				}
				else if (player == "computer1")
				{
					players.emplace_back(std::make_unique<Level1>(i));
				}
				else if (player == "computer2")
				{
					players.emplace_back(std::make_unique<Level2>(i));
				}
				else if (player == "computer3")
				{
					players.emplace_back(std::make_unique<Level3>(i));
				}
				/*} else if (player == "computer4") {
						Level4 *plyr = new Level4(); // what arguments??
						players.emplace_back(plyr);
						break;
				}*/
				else
				{
					std::cout << "invalid player :" << player << std::endl;
					break; // break to reset input
				}
			}
			viewers.emplace_back(std::make_unique<Text>(std::cout));
			// viewers.emplace_back(graphic);
		}
		else if (command == "resign")
		{ // this would need to change if >2 players- basically just check turn mod numplayers
			if (!game_running)
			{
				std::cout << "The game has ended. Please start a new game before resigning." << std::endl;
				continue;
			}
			int curplayer = turn % numplayers;
			for (int i = 0; i < numplayers; ++i)
			{
				if (i != curplayer)
				{
					wins[i]++;
				}
			}
			// effectively ends game - should delete all associated memory (board + players, maybe viewers?)
			game_running = false;
		}
		else if (command == "move")
		{
			if (!game_running)
			{
				std::cout << "The game has ended. Please start a new game before making moves." << std::endl;
				continue;
			}
			int curplayer = turn % numplayers;
			std::vector<Move> moves = board->listMoves(players[curplayer]->getColor());
			bool valid_move = false;

			if (moves.size() > 0) {
				Move playermove = players[curplayer]->getMove(board->listMoves(players[curplayer]->getColor()));
				valid_move = board->checkMove(playermove);
			}
			//updateViewers();
			if (valid_move) {
				checkEnd();
				turn++;
			} else {
				std::cout << "Invalid move. Please enter a valid move" << std::endl;
			}
		}
		/*else if (command == "setup")
		{
			if (!board)
			{
				std::cout << "The game has ended. Please start a new game before setting up." << std::endl;
				continue;
			}
			setup();
		}*/
		else
		{
			std::cout << command << " is not a valid command" << std::endl;
		}
	}
	// print final score, white wins and black wins
	// delete stuff? Or will it all be deleted in destructor?
}
/*void Game::setup()
{
	std::string command;
	if (command == "+")
	{
		char K;
		std::string e1;
		std::cin >> K >> e1;
		board->place(K, e1); //!!!!! may need new method here?? - adding new piece
	} else if (command == "-") {
		std::string e1;
		std::cin >> e1;
		board->remove(e1); //!!!!!!!!!!!! may need new method here?????
	} else if (command == "=") {
		std::string colour;
		std::cin >> colour;
		// !!!!!!!!!!!!!!!!!!!
		// should switch around order of wins as well
		// should maybe change order of players in players until the one we want is first? (can get front element (vector< >::front(players), emplace on back and then use erase??)
	} else if (command == "done") {
		if (board->doneSetUp())
		{ // need new method here??? - to check if conditions met
			return;
		}
	// check if board contains exactly one white king and one black king, no pawns are on the first or last row of the board, and neither king is in check - O.W. shouldn't leave setup mode, should output message to user
	// if the conditions are met, should return to game setup, having made changes to board
	} else {
		std::cout
			<< command << " is not a valid command, please enter one of [+ K e1], [- e1], [= colour] or [done]" << std::endl;
	}
}*/
void Game::checkEnd()
{
	bool end = false;
	int curplayer = turn % numplayers;
	int nextplayer = curplayer + 1;
	if (nextplayer >= numplayers)
	{
		nextplayer -= 0;
	}

	int state = board->checkmate(players[nextplayer]->getColor());
	if (state == 1) // checkmate
	{
		end = true;
		wins[curplayer]++;
		if (curplayer == 0) {
			std::cout << "White wins!" << std::endl;
		} else {
			std::cout << "Black wins!" << std::endl;
		}
	}
	else if (state == 2)
	{ // stalemate
		end = true;
		for (int j = 0; j<numplayers; ++j)
		{
			wins[j] += 0.5;
		}
		std::cout << "Tie." << std::endl;
	}

	if (end)
	{
		game_running = false;
	}
	// do we need to account for insufficient material end case?????????
	// do we need to add in 50-move rule or agreement or repetition?????
}
Game::~Game() {}
