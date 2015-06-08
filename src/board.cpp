#include "board.h"
#include <iostream>

Board::Board(int x, int y, int w, int h, int sqSize, int sqBrdr, Color wallColor)
	: m_wallColor(wallColor),
	  m_piece(new Piece(x + w / 2, y, sqSize, sqBrdr))
{
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;

	for(int dy = -1; dy < m_h + 1; dy++)
	{
		for(int dx = -1; dx < m_w + 1; dx++)
		{
			if(dx == -1 || dx == m_w || dy == -1 || dy == m_h)
				m_walls.push_back(Square(m_x + dx, m_y + dy, sqSize, sqBrdr, m_wallColor));
		}
	}
}


Board::~Board()
{
	delete m_piece;
}


bool Board::inBounds(int dx, int dy)
{
	bool validMove = true;

	std::vector<Square>::iterator it;
	for(it = m_piece->m_squares.begin(); it < m_piece->m_squares.end(); it++)
	{
		if(it->m_x + dx < m_x || it->m_x + dx >= m_x + m_w)
			validMove = false;
		if(it->m_y + dy >= m_y + m_h)
			validMove = false;
		if(squareColliding(it->m_x + dx, it->m_y + dy))
			validMove = false;
	}

	return validMove;
}


bool Board::inBounds(int dx, int dy, int rot)
{
	bool validMove = true;

	for(int i = 0; i < 4; i++)
	{
		int x = m_piece->m_x + PIECES[m_piece->m_type][rot][i][0] + dx;
		int y = m_piece->m_y + PIECES[m_piece->m_type][rot][i][1] + dy;

		if(x < m_x || x >= m_x + m_w || y >= m_y + m_h)
			validMove = false;
		if(squareColliding(x, y))
			validMove = false;
	}

	return validMove;
}


bool Board::pieceAtBottom()
{
	if(!inBounds(0, 1)) return true;
	else return false;
}


bool Board::squareColliding(int x, int y)
{
	bool collision = false;

	std::vector<Square>::iterator it;
	for(it = m_squares.begin(); it < m_squares.end(); it++)
	{
		if(x == it->m_x && y == it->m_y)
		{
			collision = true;
			break;
		}
	}

	return collision;
}


void Board::movePiece(int dx, int dy)
{
	if(inBounds(dx, dy))
		m_piece->move(dx, dy);
}


void Board::rotatePiece()
{
	int rot = m_piece->m_rot + 1;
	if(rot > 3) rot = 0;

	if(inBounds(0, 0, rot))
		m_piece->rotate();
}


void Board::nextPiece(Piece * newPiece, int sqSize, int sqBrdr, int * scrollTime)
{
	std::vector<Square>::iterator it;
	for(it = m_piece->m_squares.begin(); it < m_piece->m_squares.end(); it++)
	{
		m_squares.push_back(Square(it->m_x, it->m_y, sqSize, sqBrdr, m_piece->m_color));
	}

	delete m_piece;
	m_piece = new Piece(newPiece->m_type, m_x + m_w / 2, m_y, sqSize, sqBrdr, newPiece->m_color);
	if(*scrollTime > 2) *scrollTime -= 2;
}


int Board::handleCompleteRows()
{
	int res = 0;
	std::vector<int> rowCounts(m_h);
	std::vector<Square>::iterator it;
	std::vector<int>::iterator yIt;

	for(it = m_squares.begin(); it < m_squares.end(); it++)
		rowCounts[it->m_y - m_y]++;

	for(yIt = rowCounts.begin(); yIt < rowCounts.end(); yIt++)
		if(*yIt >= m_w) res++;

	for(it = m_squares.begin(); it < m_squares.end(); it++)
	{
		if(rowCounts[it->m_y - m_y] >= m_w)
		{
			m_squares.erase(it);
			it--;
		}
		else
		{
			for(yIt = rowCounts.begin() + (it->m_y - m_y); yIt < rowCounts.end(); yIt++)
				if(*yIt >= m_w) it->move(0, 1);
		}
	}

	return res;
}
