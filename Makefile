CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -g
EXEC = chess
OBJECTS = bishop.o board.o computer.o game.o graphics.o human.o king.o knight.o level1.o level2.o level3.o level4.o main.o pawn.o piece.o player.o queen.o rook.o symbols.o text.o viewer.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
