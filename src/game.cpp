#include "game.h"

Game::Game()
	: m_inputManager(new Input()),
	  m_screen(new Screen(WIDTH, HEIGHT, FONT_SIZE)),
	  m_board(new Board(BOARD_XOFF, BOARD_YOFF, BOARDW, BOARDH, CELL, CELL_BRDR, Color(100, 100, 100, 255))),
	  m_preview(new Preview(BOARD_XOFF + BOARDW + 2, BOARD_YOFF, 6, 6, CELL, CELL_BRDR, Color(200, 200, 200, 255), 0, 4))
{
	m_scrollTime = SCROLL_TIME;
	m_curFPS = (std::string)"";
	m_score = 0;
}


Game::~Game()
{
	delete m_preview;
	delete m_board;
	delete m_screen;
	delete m_inputManager;
}


void Game::run()
{
	double targetTime = 1000 / FPS, actualTime;
	double frameStart, frameEnd;
	double scrollStart = (double)SDL_GetTicks();

	m_state = PLAY;
	while(m_state != QUIT)
	{
		frameStart = (double)SDL_GetTicks();

		handleEvents();
		tick(&scrollStart);
		render();

		frameEnd = (double)SDL_GetTicks();
		actualTime = frameEnd - frameStart;
		if(actualTime < targetTime)
		{
			SDL_Delay((Uint32)(targetTime - actualTime));
			m_curFPS = std::to_string((int)(1000.0 / ((double)SDL_GetTicks() - frameStart)));
		}
	}
}


void Game::handleEvents()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_QUIT:
				m_state = QUIT;
				break;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym)
				{
					case SDLK_LEFT: m_inputManager->pressKey(SDLK_LEFT); break;
					case SDLK_RIGHT: m_inputManager->pressKey(SDLK_RIGHT); break;
					case SDLK_DOWN: m_inputManager->pressKey(SDLK_DOWN); break;
					case SDLK_UP: m_inputManager->pressKey(SDLK_UP); break;
					case SDLK_ESCAPE: m_inputManager->pressKey(SDLK_ESCAPE); break;
				}
				break;
		}
	}
}


void Game::tick(double * scrollStart)
{
	m_score += m_board->handleCompleteRows();

	double scrollCheck = (double)SDL_GetTicks();
	if(scrollCheck - *scrollStart >= m_scrollTime)
	{
		if(!m_board->pieceAtBottom())
		{
			m_board->movePiece(0, 1);
		}
		else
		{
			m_board->nextPiece(m_preview->m_piece, CELL, CELL_BRDR, &m_scrollTime);
			m_preview->nextPiece(CELL, CELL_BRDR);
		}
		*scrollStart = scrollCheck;
	}

	std::vector<SDL_Keycode>::iterator it;
	for(it = m_inputManager->m_events.begin(); it < m_inputManager->m_events.end(); it++)
	{
		switch(*it)
		{
			case SDLK_LEFT: m_board->movePiece(-1, 0); break;
			case SDLK_RIGHT: m_board->movePiece(1, 0); break;
			case SDLK_DOWN: m_board->movePiece(0, 1); break;
			case SDLK_UP: m_board->rotatePiece(); break;
			case SDLK_ESCAPE: m_state = PAUSE; break;
		}
	}
	m_inputManager->purgeEvents();
}


void Game::render()
{
	// Black bg
	m_screen->setColor(0, 0, 0, 255);
	m_screen->clear();

	// Text
	m_screen->drawText(m_curFPS, 5, 5);
	std::string scoreString = "Score: " + std::to_string(m_score);
	int scoreX = (m_preview->m_x + 1) * CELL_SIZE;
	int scoreY = (m_preview->m_y + m_preview->m_h + 2) * CELL_SIZE;
	m_screen->drawText(scoreString, scoreX, scoreY);

	std::vector<Square>::iterator it;

	// Board walls
	m_screen->setColor(m_board->m_wallColor);
	for(it = m_board->m_walls.begin(); it < m_board->m_walls.end(); it++)
		m_screen->drawRect(&it->m_pixels);

	// Preview walls
	m_screen->setColor(m_preview->m_wallColor);
	for(it = m_preview->m_walls.begin(); it < m_preview->m_walls.end(); it++)
		m_screen->drawRect(&it->m_pixels);

	// Squares
	for(it = m_board->m_squares.begin(); it < m_board->m_squares.end(); it++)
	{
		m_screen->setColor(it->m_color);
		m_screen->drawRect(&it->m_pixels);
	}
	
	// Piece
	m_screen->setColor(m_board->m_piece->m_color);
	for(it = m_board->m_piece->m_squares.begin(); it < m_board->m_piece->m_squares.end(); it++)
	{
		if(it->m_y - m_board->m_y >= 0)
			m_screen->drawRect(&it->m_pixels);
	}

	// Preview Piece
	m_screen->setColor(m_preview->m_piece->m_color);
	for(it = m_preview->m_piece->m_squares.begin(); it < m_preview->m_piece->m_squares.end(); it++)
	{
		if(it->m_y - m_preview->m_y >= 0)
			m_screen->drawRect(&it->m_pixels);
	}

	m_screen->present();
}
