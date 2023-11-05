// This file is to test the game engine

#include "Engine.h"
#include "Log.h"
#include "Resources/Texture.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


using namespace Perch;


int main(int argc, char* args[])
{
	Engine* window = new Engine(SCREEN_WIDTH, SCREEN_HEIGHT);


	Texture* texture = Texture::Create(window->GetMainWindowSurface(), "./images/squawky_birb.bmp", Texture::FORMAT_BMP);
	if (texture == NULL)
	{
		return -1;
	}

	if (!window->Create())
	{
		return -1;
	}

	//window->BlitSurfaceScaled(texture);

	window->Start();


	return 0;
}
