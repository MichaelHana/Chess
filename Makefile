CXX=g++
CXXFLAGS= -std=c++14 -Wall -g -MMD
OBJECTS=bishop.o board.o computer.o game.o graphics.o human.o king.o knight.o level1.o level2.o level3.o main.o pawn.o piece.o player.o queen.o rook.o symbols.o text.o viewer.o window.o
EXEC=chess
${EXEC}:${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lX11
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${EXEC} ${OBJECTS} ${DEPENDS}
