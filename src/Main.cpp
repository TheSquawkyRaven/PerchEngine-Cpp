// This file is to test the game engine

#include "Engine.h"
#include "Log.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char* args[])
{
	Engine* window = new Engine(SCREEN_WIDTH, SCREEN_HEIGHT);
	Log::Printf("Hello %s, I am %s. %d", "World", "Raven", 22);
	Log::Error("TESET ERROR");

	if (!window->InitializeMainWindow())
	{
		return -1;
	}
	window->Start();


	return 0;
}
