#include "Board.h"

Board::Board(Graphics & gfx)
	:
gfx(gfx)
{
}

void Board::DrawGrid(const Location loc, Color c)
{
	const int off_x = x + borderwidth + borderPadding;
	const int off_y = y + borderPadding + borderwidth;
	gfx.DrawRectDim(loc.x * dimension + off_x+cellPadding, loc.y * dimension+off_y+cellPadding, dimension-cellPadding*2, dimension-cellPadding*2, c);
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location loc) const
{
	return (loc.x >= 0 && loc.x < width  &&
		loc.y >= 0 && loc.y < height);
}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;
	const int bottom = top + (borderwidth + borderPadding) * 2 + height*dimension;
	const int right = left + (borderwidth + borderPadding) * 2 + width*dimension;

	//top
	gfx.DrawRect(left, top, right, top+borderwidth,borderColor);
	//left
	gfx.DrawRect(left, top + borderwidth, left + borderwidth, bottom - borderwidth, borderColor);
	//bottom
	gfx.DrawRect(left, bottom - borderwidth, right, bottom, borderColor);
	//right
	gfx.DrawRect(right - borderwidth, top+borderwidth, right, bottom, borderColor);
}


