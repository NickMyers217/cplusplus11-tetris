#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include "color.h"

class Screen
{
public:
	int m_width;
	int m_height;
	SDL_Window * m_window;
	SDL_Renderer * m_renderer;
	int m_fontSize;
	TTF_Font * m_font;
	SDL_Color m_textColor;

	Screen(int w, int h, int fontSize);
	~Screen();
	void clear();
	void setColor(Color c);
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void drawRect(SDL_Rect * rect);
	void drawTexture(SDL_Texture * tex, int x, int y, SDL_Rect * clip);
	void drawText(std::string & text, int x, int y);
	void present();
};

#endif
