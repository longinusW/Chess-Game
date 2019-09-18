CXX = g++
CXXFLAGS = -g -std=c++14 -Werror=vla -Wall -MMD
#CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chess
OBJECTS = main.o piece.o board.o textdisplay.o king.o queen.o rook.o bishop.o pawn.o knight.o game.o player.o human.o compl1.o compl2.o compl3.o compl4.o computer.o graphicsdisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
