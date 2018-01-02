/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include"sprites.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx),
	snake({ 2,2 }),
	rng(std::random_device()()),
	goal(rng,brd,snake)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (isgamestarted) {
		if (isgameover == false) {
			if (wnd.kbd.KeyIsPressed(VK_UP) && up == true) {
				delta_loc = { 0,-1 };
				up = true;
				down = false;
				left = true;
				right = true;
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN) && down == true) {
				delta_loc = { 0,1 };
				up = false;
				down = true;
				left = true;
				right = true;
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT) && right == true) {
				delta_loc = { 1,0 };
				up = true;
				down = true;
				left = false;
				right = true;
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT) && left == true) {
				delta_loc = { -1,0 };
				up = true;
				down = true;
				left = true;
				right = false;;
			}


			moveCounter++;
			if (moveCounter >= movePeriod) {
				moveCounter = 0;
				const Location next = snake.GetNextHeadLocation(delta_loc);
				if (!brd.IsInsideBoard(next) || snake.IsInTileExceptEnd(next)) {
					isgameover = true;
				}
				else {
					const bool iseating = (next == goal.GetLocation());
					if (iseating) {
						snake.Grow();
						speedcounter++;
					}
					snake.MoveBy(delta_loc);
					if (iseating) {
						goal.Respawn(rng, brd, snake);
					}
				}
				if (speedcounter == 3) {
					speedcounter = 0;
					movePeriod--;
					if (movePeriod < movePeriodMin) {
						movePeriod = movePeriodMin;
					}
				}
			}
		}
	}
	else {
		isgamestarted = wnd.kbd.KeyIsPressed(VK_RETURN);
	}
	
}

void Game::ComposeFrame()
{
	if (!isgamestarted) {
		Sprites::TitleScreen(300,225,gfx);
	}
	else {
		snake.Draw(brd);
		++flashCounter;
		if (flashCounter > dimGoal) {
				goal.Draw(brd);
				if(flashCounter==flashGoal){
					flashCounter = 0;
				}
		}
	
		if (isgameover == true) {
			Sprites::DrawGameOver(358, 258, gfx);
		}
		brd.DrawBorder();
	}
}
	

void Game::Test() {

}



	


