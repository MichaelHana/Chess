#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "move.h"
#include "board.h"
#include "player.h"
#include "viewer.h"

class Game {
	int turn = 0;
	static const int numplayers = 2;
	int rows = 8;
	int cols = 8;
	bool game_running;
	
	std::vector<double> wins = std::vector<double>(numplayers, 0);
	std::vector<std::vector<char>> start;
	std::unique_ptr<Board> board;
	std::vector<std::unique_ptr<Player>> players;
	std::vector<std::unique_ptr<Viewer>> viewers;
	std::vector<Move> move_history;
public:
	void play();//main game
	void updateViewers();//updates text and graphic viewers
	void setup();//setup mode
	void checkEnd();//check for game end
	~Game();
};
#endif
