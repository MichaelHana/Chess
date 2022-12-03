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
#include <string>
#include <iostream>
#include <vector>

void Game::updateViewers()
{
	char cur[rows][cols] = board->getState();
	for (Viewer *viewer : viewers)
	{
		viewer->update(cur);
	}
}

void Game::play()
{
	Text *text = new Text(std::cout); // This is fine - if wanted to change layout, would need to implemenet new viewer and Text constructors to take in rows and cols
	// Graphics *graphic = new Graphic(); // This is fine - if wanted to change layout etc, would need to implement new viewer and graphics ctors, would just add parameters rows, columns, start

	std::string command;
	while (std::cin >> command)
	{
		if (command == "game")
		{
			//int row = rows;
			//int col = cols;
			// reset turn to 0
			// delete current board, players, viewers(??)? will this have - should actually just do this when game ends so players can't keep making moves on an already finished game
			board = new Board(rows, cols, start);
			for (int i = 0; i < numplayers; ++i)
			{
				std::string player;
				std::cin >> player;
				// Player *plyr;
				if (player == "human")
				{
					Human *plyr = new Human(std::cin);
					players.emplace_back(plyr);
				}
				else if (player == "computer1")
				{
					Level1 *plyr = new Level1(); // what arguments??
					players.emplace_back(plyr);
				}
				else if (player == "computer2")
				{
					Level2 *plyr = new Level2(); // what arguments??
					players.emplace_back(plyr);
				}
				else if (player == "computer3")
				{
					Level3 *plyr = new Level3(); // what arguments??
					players.emplace_back(plyr);
					/*} else if (player == "computer4") {
						Level4 *plyr = new Level4(); // what arguments??
						players.emplace_back(plyr);
						break;*/
				}
				else
				{
					std::cout << "invalid player :" << player << std::endl;
					break;
					// should this break and reset everything??
				}
			}
			viewers.emplace_back(text);
			// viewers.emplace_back(graphic);
		}
		else if (command == "resign")
		{ // this would need to change if >2 players- basically just check turn mod numplayers
			if (!board)
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
			delete board;
			board = nullptr;
			for (int i = 0; i < numplayers; ++i)
			{
				delete players.back();
				players.pop_back();
			} //?????
		}
		else if (command == "move")
		{
			if (!board)
			{
				std::cout << "The game has ended. Please start a new game before making moves." << std::endl;
				continue;
			}
			int curplayer = turn % numplayers;
			// vector<Move *> validmoves = board.listmoves(); //ensure its not empty!!!
			Move playermove = players[curplayer]->getMove(board.listmoves()); //std::pair<std::pair<int, int>, std::pair<int, int>>
			board->checkMove(playermove);
			updateViewers();
			// get player move - what is the type I should take it as??
			//  update board with move - checkmove??
			// call updateviewers with argument from board.getstate()
			checkEnd();
			turn++;
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
int Game::checkEnd()
{
	bool end = false;
	int curplayer = turn % numplayers;
	int nextplayer = curplayer + 1;
	if (nextplayer >= numplayers)
	{
		nextplayer -= numplayers;
	}

	/*for (Player *player : players)
	{
		int state = board->checkmate(player->colour);
		if (state == 1) //checkmate
		{ // what are conditions for win/end??????? just checkmate???
			end = true;
			wins[curplayer]++; //curplayer shouldn't be in check since they can't move themselves into check
			// win?? add to one player's score?????
			//
		} else if (state == 2) { //stalemate
			end = true;
			for (j=0; j< numplayers; ++j) {
				wins[j] += 0.5;
			}
		}
		// if end, update wins, and delete board, players
	}*/
	int state = board->checkmate(players[nextplayer]->colour);
	if (state == 1) // checkmate
	{				// what are conditions for win/end??????? just checkmate???
		end = true;
		wins[curplayer]++; // curplayer shouldn't be in check since they can't move themselves into check
						   // win?? add to one player's score?????
						   //
	}
	else if (state == 2)
	{ // stalemate
		end = true;
		for (j = 0; j < numplayers; ++j)
		{
			wins[j] += 0.5;
		}
	}
	if (end)
	{
		delete board;
		board = nullptr;
		for (int i = 0; i < numplayers; ++i)
		{
			delete vector<Player *>::back(players);
			players.pop_back();
		}
		// delete all players
	}
	// do we need to account for insufficient material end case?????????
	// do we need to add in 50-move rule or agreement or repetition?????
}
Game::~Game
{
	while (viewers[0])
	{
		delete vector<Viewer *>::back(viewers);
		viewers.pop_back();
	} //?????
	  // is there any case here where I should also delete board and players??
}
