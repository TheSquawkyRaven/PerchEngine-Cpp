#include "Engine.h"

void Engine::SetScreenWidth(int width)
{
	ScreenWidth = width;
}

void Engine::SetScreenHeight(int height)
{
	ScreenHeight = height;
}

Engine::Engine(int ScreenHeight, int ScreenWidth)
{
	this->ScreenWidth = ScreenWidth;
	this->ScreenHeight = ScreenHeight;
}

Engine* Engine::Create()
{
	// Initialize SDL Video Graphics
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		
	}
	return this;
}
