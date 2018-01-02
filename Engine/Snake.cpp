#include "Snake.h"
#include<assert.h>



void Snake::Grow()
{
	if (nSegment < maxSegments) {
		nSegment++;
	}
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = nSegment-1 ;i > 0;i--) {
		segments[i].Follow(segments[i-1]);
	}
	segments[0].MoveBy(delta_loc);
}

Snake::Snake(const Location& delta_loc)
{
	constexpr int nBodycolor = 4;
	constexpr Color bodyColors[nBodycolor] = { {10,100,32},{10,130,48},{18,160,48},{10,130,48} };
	for (int i = 1;i < maxSegments;i++) {
		segments[i].InitBody(bodyColors[i%nBodycolor]);
	}
	segments[0].InitHead(delta_loc);
}

void Snake::Draw(Board & brd) const
{
	for (int i = 0;i < nSegment;i++) {
		segments[i].Draw(brd);
	}
}

Location Snake::GetNextHeadLocation(const Location & loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(loc);
	return l;
}

bool Snake::IsInTileExceptEnd(const Location & tile) const
{
	for (int i = 0;i < nSegment-1;i++) {
		if (segments[i].GetLocation() == tile) {
			return true;
		}
	}
	return false;
}

bool Snake::IsInTile(const Location & tile) const
{
	for (int i = 0;i < nSegment;i++) {
		if (segments[i].GetLocation() == tile) {
			return true;
		}
	}
	return false;
}

void Snake::Segment::InitHead(const Location delta_loc)
{
	loc = delta_loc;
	c = Snake::headColor;
}

void Snake::Segment::Follow(const Segment next)
{
	
	loc = next.loc;
	
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::InitBody(Color c_in)
{
	c = c_in;
}

void Snake::Segment::Draw(Board & brd) const
{
	brd.DrawGrid(loc, c);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
