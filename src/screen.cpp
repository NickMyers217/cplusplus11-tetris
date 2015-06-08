#include "screen.h"

Screen::Screen(int w, int h, int fontSize)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	m_window = nullptr;
	m_renderer = nullptr;
	
	if(SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, &m_window, &m_renderer) < 0)
		std::cerr << "Error initializing window and renderer." << std::endl;

	if(TTF_Init() < 0)
		std::cerr << "Error initializing ttf." << std::endl;

	m_fontSize = fontSize;
	m_font = TTF_OpenFont("./res/font.ttf", m_fontSize);
	m_textColor = { 255, 255, 50, 255};
}

Screen::~Screen()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	TTF_CloseFont(m_font);
	TTF_Quit();
	SDL_Quit();
}


void Screen::clear()
{
	SDL_RenderClear(m_renderer);
}


void Screen::setColor(Color c)
{
	SDL_SetRenderDrawColor(m_renderer, c.m_r, c.m_g, c.m_b, c.m_a);
}


void Screen::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}


void Screen::drawRect(SDL_Rect * rect)
{
	SDL_RenderFillRect(m_renderer, rect);
}


void Screen::drawTexture(SDL_Texture * tex, int x, int y, SDL_Rect * clip = nullptr)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr)
	{
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else
	{
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}
	SDL_RenderCopy(m_renderer, tex, clip, &dst);
}


void Screen::drawText(std::string & text, int x, int y)
{
	SDL_Surface * surf = TTF_RenderUTF8_Solid(m_font, text.c_str(), m_textColor);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(m_renderer, surf);
	drawTexture(texture, x, y);
}


void Screen::present()
{
	SDL_RenderPresent(m_renderer);
}
