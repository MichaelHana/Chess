CXX=g++
CXXFLAGS= -std=c++14 -Wall -g -MMD
OBJECTS=bishop.o board.o computer.o game.o graphics.o human.o king.o knight.o level1.o level2.o level3.o main.o move.o pawn.o piece.o player.o queen.o rook.o symbols.o text.o viewer.o window.o
EXEC=chess
${EXEC}:${OBJECTS}
	${CSS} ${OBJECTS} -o ${EXEC} -1Xll
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${EXEC} ${OBJECTS} ${DEPENDS}
