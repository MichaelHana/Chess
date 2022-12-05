#include <string>
#include <iostream>
#include "game.h"

int main() {
	std::unique_ptr<Game> game = std::make_unique<Game>();
	game->play();
}
