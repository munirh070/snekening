#pragma once
#include"Graphics.h"
#include"Location.h"


class Board{
public:
	Board(Graphics& gfx);
	void DrawGrid(const Location loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location loc) const;
	void DrawBorder();

private:
	static constexpr int cellPadding = 1;
	static constexpr Color borderColor = Colors::Blue;
	static constexpr int dimension = 10;
	static constexpr int width = 75;
	static constexpr int height = 55;
	static constexpr int x = 20;
	static constexpr int y = 20;
	static constexpr int borderwidth = 4;
	static constexpr int borderPadding = 1;
	Graphics& gfx;

};