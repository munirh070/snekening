#pragma once

#include"Board.h"

class Snake {
private:
	class Segment {
	public:
		void InitHead(const Location delta_loc);
		void Follow(const Segment next);
		void MoveBy(const Location& delta_loc);
		void InitBody(Color c);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};

public:
	void Grow();
	void MoveBy(const Location& delta_loc);
	Snake(const Location& delta_loc);
	void Draw(Board& brd) const;
	Location GetNextHeadLocation(const Location& loc) const;
	bool IsInTileExceptEnd(const Location& tile) const;
	bool IsInTile(const Location& tile) const;
	

private:
	static constexpr int maxSegments = 100;
	Segment segments[maxSegments];
	static constexpr Color headColor = Colors::Yellow;
	 int nSegment = 1;


};
