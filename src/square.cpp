#include "square.h"

Square::Square(int x, int y, int size, int brdr, Color color)
	: m_color(color)
{
	m_x = x;
	m_y = y;
	m_brdr = brdr;
	m_size = size;
	adjustPixels();
}


Square::~Square()
{
}


void Square::adjustPixels()
{
	m_pixels.x = (m_brdr + m_size) * m_x;
	m_pixels.y = (m_brdr + m_size) * m_y;
	m_pixels.w = m_size;
	m_pixels.h = m_size;
}


void Square::move(int dx, int dy)
{
	m_x += dx;
	m_y += dy;
	adjustPixels();
}
