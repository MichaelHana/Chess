#include "game.h"
#include "human.h"
#include "computer.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
// include "level4.h"
#include "text.h"
#include "graphics.h"
#include <string>
#include <iostream>
// include <vector>

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
	Text *text = new Text(std::cout);  // This is fine - if wanted to change layout, would need to implemenet new viewer and Text constructors to take in rows and cols
	Graphics *graphic = new Graphic(); // This is fine - if wanted to change layout etc, would need to implement new viewer and graphics ctors, would just add parameters rows, columns, start

	std::string command;
	while (std::cin >> command)
	{
		switch (command)
		{
		case "game":
			// reset turn to 0
			// delete current board, players, viewers(??)? will this have - should actually just do this when game ends so players can't keep making moves on an already finished game
			board = new Board(start);
			for (int i = 0; i < numplayers; ++i)
			{
				std::string player;
				std::cin >> player;
				switch (player1)
				{
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
				/*case "computer4":
					Level4 *plyr = new Level4(); // what arguments??
					break;*/
				default:
					std::cout << invalid player : << player << std::endl;
					// should this break and reset everything??
				}
				players.emplace_back(plyr);
			}
			viewers.emplace_back(text);
			viewers.emplace_back(graphic);
			break;
		case "resign": // this would need to change if >2 players- basically just check turn mod numplayers
			if (!board)
			{
				std::cout << "The game has ended. Please start a new game before resigning." << std::endl;
				break;
			}
			curplayer = turn % numplayers;
			for (int i = 0; i < numplayers)
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
				delete vector<Player *>::back(players);
				players.pop_back();
			} //?????
			break;
		case "move":
			if (!board)
			{
				std::cout << "The game has ended. Please start a new game before making moves." << std::endl;
				break;
			}
			curplayer = turn % numplayers;
			// vector<Move *> validmoves = board.listmoves(); //ensure its not empty!!!
			std::pair<std::pair<int, int>, std::pair<int, int>> playermove = players[curplayer]->getMove(board.listmoves());
			board->move(playermove);
			updateViewers();
			// get player move - what is the type I should take it as??
			//  update board with move - checkmove??
			// call updateviewers with argument from board.getstate()
			checkEnd();
			break;
		case "setup":
			if (!board)
			{
				std::cout << "The game has ended. Please start a new game before setting up." << std::endl;
				break;
			}
			setup();
			break;
		default:
			std::cout << command << " is not a valid command" << std::endl;
		}
	}
	// print final score, white wins and black wins
	// delete stuff? Or will it all be deleted in destructor?
}
void setup()
{
	std::string command;
	switch (command)
	{
	case "+":
		char K;
		std::string e1;
		std::cin >> K >> e1;
		board.place(K, e1); //!!!!! may need new method here?? - adding new piece
	case "-":
		std::string e1;
		std::cin >> e1;
		board.remove(e1); //!!!!!!!!!!!! may need new method here?????
	case "=":
		std::string colour;
		std::cin >> colour;
		// !!!!!!!!!!!!!!!!!!!
		// should switch around order of wins as well 
		// should maybe change order of players in players until the one we want is first? (can get front element (vector< >::front(players), emplace on back and then use erase??)
	case "done":
		if (board.doneSetUp())
		{ // need new method here??? - to check if conditions met
			return;
		}
		break;
	// check if board contains exactly one white king and one black king, no pawns are on the first or last row of the board, and neither king is in check - O.W. shouldn't leave setup mode, should output message to user
	// if the conditions are met, should return to game setup, having made changes to board
	default:
		std::cout
			<< command << " is not a valid command, please enter one of [+ K e1], [- e1], [= colour] or [done]" << std::endl;
	}
}
int checkEnd()
{
	bool end = false;
	curplayer = turn % numplayers;
	nextplayer = curplayer + 1;
	if (nextplayer >= numplayers)
	{
		nextplayer -= numplayers;
	}
	if (!players[nextplayer]->getMove(board.listmoves()))
	{ // what does it return if no moves??
		end = true;
		for (j=0; j< numplayers; ++j) {
			wins[j] += 0.5;
		}
		// draw?? - add .5 to each player's score??? - is this a stalemate???
	}
	else
	{
		for (Player *player : players)
		{
			int state = board->checkmate(player->colour);
			if (state ==)
			{ // what are conditions for win/end??????? just checkmate???
				end = true;
				wins[curplayer]++; //curplayer shouldn't be in check since they can't move themselves into check
				// win?? add to one player's score?????
				//
			}
			// if end, update wins, and delete board, players
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
