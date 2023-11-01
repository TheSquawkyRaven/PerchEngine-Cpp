#pragma once

// Main SDL Window
#include <SDL.h>

// Standard Input and Output Library (for IO streams with keyboard input, file support etc)
#include <stdio.h>

class Engine
{
private:

	int ScreenWidth;
	int ScreenHeight;

public:

	void SetScreenWidth(int width);
	void SetScreenHeight(int height);

	inline int GetScreenWidth() { return ScreenWidth; }
	inline int GetScreenHeight() { return ScreenHeight; }

private:

	// SDL Window for rendering into
	SDL_Window* SDL_Window = nullptr;

	SDL_Surface* SDL_Surface = nullptr;

public:

	Engine(int ScreenWidth = 480, int ScreenHeight = 640);

	Engine* Create();



};

