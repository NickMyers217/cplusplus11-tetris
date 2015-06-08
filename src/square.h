#ifndef SQUARE_H
#define SQUARE_H

#include <SDL2/SDL.h>
#include "color.h"

class Square
{
public:
	int m_x;
	int m_y;
	int m_brdr;
	int m_size;
	Color m_color;
	SDL_Rect m_pixels;

	Square(int x, int y, int size, int brdr, Color color);
	~Square();
	void adjustPixels();
	void move(int dx, int dy);
};

#endif
