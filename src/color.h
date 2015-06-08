#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>

struct Color
{
	Uint8 m_r;
	Uint8 m_g;
	Uint8 m_b;
	Uint8 m_a;

	Color(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255)
	{
		m_r = r;
		m_g = g;
		m_b = b;
		m_a = a;
	}
};

#endif
