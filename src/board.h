#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "piece.h"
#include "square.h"
#include "color.h"

class Board
{
public:
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	Color m_wallColor;
	std::vector<Square> m_walls;
	std::vector<Square> m_squares;
	Piece * m_piece;

	Board(int x, int y, int w, int h, int sqSize, int sqBrdr, Color wallColor);
	~Board();
	bool inBounds(int dx, int dy);
	bool inBounds(int dx, int dy, int rot);
	bool pieceAtBottom();
	bool squareColliding(int x, int y);
	void movePiece(int dx, int dy);
	void rotatePiece();
	void nextPiece(Piece * newPiece, int sqSize, int sqBrdr, int * scrollTime);
	int handleCompleteRows();
};

#endif
