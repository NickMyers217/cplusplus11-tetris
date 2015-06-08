#include "piece.h"
#include "util.h"

Piece::Piece(Tetrinome type, int xOff, int yOff, int sqSize, int sqBrdr, Color color)
	: m_color(color)
{
	init(type, xOff, yOff, sqSize, sqBrdr, color);
}


Piece::Piece(int xOff, int yOff, int sqSize, int sqBrdr)
{
	Tetrinome type;
	switch(Util::random(0, 7))
	{
		case 0: type = O; break;
		case 1: type = I; break;
		case 2: type = J; break;
		case 3: type = L; break;
		case 4: type = S; break;
		case 5: type = Z; break;
		case 6: type = T; break;
	}

	Color color;
	switch(Util::random(0, 6))
	{
		case 0: color = Color(255, 0, 0, 255); break;
		case 1: color = Color(0, 255, 0, 255); break;
		case 2: color = Color(0, 0, 255, 255); break;
		case 3: color = Color(255, 255, 0, 255); break;
		case 4: color = Color(255, 0, 255, 255); break;
		case 5: color = Color(0, 255, 255, 255); break;
	}

	init(type, xOff, yOff, sqSize, sqBrdr, color);
}


Piece::~Piece()
{
}


void Piece::init(Tetrinome type, int xOff, int yOff, int sqSize, int sqBrdr, Color color)
{
	m_type = type;
	m_x = xOff + START_COORDS[m_type][0];
	m_y = yOff + START_COORDS[m_type][1];
	m_rot = 0;
	m_color = color;

	for(int i = 0; i < 4; i++)
	{
		int dx = PIECES[m_type][m_rot][i][0];
		int dy = PIECES[m_type][m_rot][i][1];

		m_squares.push_back(Square(m_x + dx, m_y + dy, sqSize, sqBrdr, m_color));
	}
}


void Piece::move(int dx, int dy)
{
	m_x += dx;
	m_y += dy;

	std::vector<Square>::iterator it;
	for(it = m_squares.begin(); it < m_squares.end(); it++)
	{
		it->move(dx, dy);
	}
}


void Piece::rotate()
{
	if(m_rot == 3) m_rot = 0;
	else m_rot++;

	std::vector<Square>::iterator it;
	int i;
	for(it = m_squares.begin(), i = 0; it < m_squares.end(); it++, i++)
	{
		int dx = PIECES[m_type][m_rot][i][0];
		int dy = PIECES[m_type][m_rot][i][1];
		it->m_x = m_x + dx;
		it->m_y = m_y + dy;
		it->adjustPixels();
	}
}
