#include <cstdlib>
#include <ctime>
#include "computer.h"

Computer::Computer(int color) : Player{ color } {}

char Computer::getPromotion() {
	srand(time(nullptr));

	int random = rand() % 4;

	if (this->getColor() == 0) {//white
		if (random == 0) {
			return 'Q';
		} else if (random == 1) {
			return 'N';
		} else if (random == 2) {
			return 'B';
		} else {
			return 'R';
		}
	} else if (this->getColor() == 1) {
		if (random == 0) {
			return 'q';
		} else if (random == 1) {
			return 'n';
		} else if (random == 2) {
			return 'b';
		} else {
			return 'r';
		}
	}
	return ' ';
}
