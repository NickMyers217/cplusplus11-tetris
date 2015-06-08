CC = g++
FLAGS = -Wall -std=c++11 -lSDL2 -lSDL2_ttf
SRCPATH = ./src/
SOURCES = \
	$(SRCPATH)main.cpp \
	$(SRCPATH)screen.cpp \
	$(SRCPATH)game.cpp \
	$(SRCPATH)board.cpp \
	$(SRCPATH)preview.cpp \
	$(SRCPATH)piece.cpp \
	$(SRCPATH)square.cpp
EXECUTABLE = tetris

all:
	$(CC) $(SOURCES) -o $(EXECUTABLE) $(FLAGS)

clean:
	rm $(EXECUTABLE)

