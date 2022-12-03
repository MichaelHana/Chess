#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include "board.h"

class Player;
class Viewer;

class Game {
	int turn = 0;
	static const int numplayers = 2;
	int rows = 8;//static const int rows = 8;
	int cols = 8;//static const int cols = 8;
	float wins[numplayers] = {0, 0};
	char** start; //[rows][cols] = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
	Board *board = nullptr;
	std::vector<Player *> players; //?
	std::vector<Viewer *> viewers; //?
public:
	void play();
	void updateViewers();
	void setup();
	void checkEnd();
	~Game();
};
#endif