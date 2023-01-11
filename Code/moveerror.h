#ifndef MOVEERROR_H
#define MOVEERROR_H
#include <string>

class MoveError {
	std::string msg;
	public:
		MoveError(std::string msg): msg{msg} {};
		std::string what() const { return msg; };
};
#endif
