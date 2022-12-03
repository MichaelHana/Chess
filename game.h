#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <memory>
#include "board.h"
#include "viewer.h"

class Player;

class Game {
	int turn = 0;
	static const int numplayers = 2;
	int rows = 8;//static const int rows = 8;
	int cols = 8;//static const int cols = 8;
	float wins[numplayers] = {0, 0};
	bool game_running;
	std::vector<std::vector<char>> start; //[rows][cols] = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
	std::unique_ptr<Board> board = nullptr;
	std::vector<std::unique_ptr<Player>> players; //?
	std::vector<std::unique_ptr<Viewer>> viewers; //?
public:
	void play();
	void updateViewers();
	void setup();
	void checkEnd();
	~Game();
};
#endif