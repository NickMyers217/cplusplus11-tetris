#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "tetrinomes.h"
#include "color.h"
#include "square.h"

class Piece
{
public:
	Tetrinome m_type;
	int m_x;
	int m_y;
	int m_rot;
	Color m_color;
	std::vector<Square> m_squares;
	
	Piece(Tetrinome type, int xOff, int yOff, int sqSize, int sqBrdr, Color color);
	Piece(int xOff, int yOff, int sqSize, int sqBrdr);
	~Piece();
	void init(Tetrinome type, int xOff, int yOff, int sqSize, int sqBrdr, Color color);
	void move(int dx, int dy);
	void rotate();
};

#endif
