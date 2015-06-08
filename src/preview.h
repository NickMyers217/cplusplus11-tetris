#ifndef PREVIEW_H
#define PREVIEW_H

#include "board.h"

class Preview : public Board
{
public:
	int m_pieceXOff;
	int m_pieceYOff;

	Preview(int x, int y, int w, int h, int sqSize, int sqBrdr, Color wallColor, int pXOff, int pYOff);
	~Preview();
	void nextPiece(int sqSize, int sqBrdr);
};

#endif
