#ifndef GAME_H
#define GAME_H

#include <string>
#include "screen.h"
#include "color.h"
#include "board.h"
#include "preview.h"
#include "piece.h"
#include "square.h"
#include "input.h"

class Game
{
public:
	static const int WIDTH = 1920;
	static const int HEIGHT = 1080;
	static const int FONT_SIZE = 32;
	static const int CELL_SIZE = 40;
	static const int CELL_BRDR = 4;
	static const int CELL = CELL_SIZE - CELL_BRDR;
	static const int BOARDW = 10;
	static const int BOARDH = 20;
	static const int BOARD_XOFF = (WIDTH / CELL_SIZE / 2) - (BOARDW / 2);
	static const int BOARD_XMID = BOARD_XOFF + (BOARDW / 2);
	static const int BOARD_YOFF = (HEIGHT / CELL_SIZE / 2) - (BOARDH / 2);
	static const int FPS = 60;
	static const int SCROLL_TIME = 1000;

	enum GameState { PLAY, PAUSE, LOSS, QUIT };

	GameState m_state;
	Input * m_inputManager;
	Screen * m_screen;
	Board * m_board;
	Preview * m_preview;
	int m_scrollTime;
	int m_score;
	std::string m_curFPS;

	Game();
	~Game();
	void run();
	void handleEvents();
	void tick(double * scrollStart);
	void render();
};

#endif
