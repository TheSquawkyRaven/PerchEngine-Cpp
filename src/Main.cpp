// This file is to test the game engine

#include "Engine.h"
#include "Log.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char* args[])
{
	Perch::Engine* window = new Perch::Engine(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (!window->InitializeMainWindow())
	{
		return -1;
	}

	SDL_Surface* testSurface = window->LoadBmpSurface("./images/squawky_birb.bmp");
	if (testSurface == NULL)
	{
		return -1;
	}

	window->BlitSurfaceScaled(testSurface);

	window->Start();


	return 0;
}
