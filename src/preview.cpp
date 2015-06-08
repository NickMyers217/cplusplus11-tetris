#include "preview.h"

Preview::Preview(int x, int y, int w, int h, int sqSize, int sqBrdr, Color wallColor, int pXOff, int pYOff)
	 : Board(x, y, w, h, sqSize, sqBrdr, wallColor)
{
	m_pieceXOff = pXOff;
	m_pieceYOff = pYOff;
	movePiece(m_pieceXOff, m_pieceYOff);
}


Preview::~Preview()
{
}


void Preview::nextPiece(int sqSize, int sqBrdr)
{
	delete m_piece;
	m_piece = new Piece((m_x + m_w / 2) + m_pieceXOff, m_y + m_pieceYOff, sqSize, sqBrdr);
}
