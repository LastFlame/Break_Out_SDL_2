#include "stdafx.h"
#include "Engine.h"
#include "Break_Out.h"





//const ptr a contents of the pointer cannot be changed
//ptr const a pointer can't be changed.

int main(int argc, char* args[])
{
	Break_Out breakout;

	breakout.Init_Sys();

	/*breakout.Init_Font("Assets/lazy.ttf", 32);*/

	breakout.Init_Window("Break out", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 610, 800, 0);

	breakout.Start_Game();

	return 0;
}




