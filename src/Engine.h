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
	SDL_Window* MainWindow = nullptr;

	SDL_Surface* MainWindowSurface = nullptr;

public:

	Engine(int ScreenWidth = 480, int ScreenHeight = 640);

	bool InitializeMainWindow();

	// "Start" here will wait for until the closure of the MainWindow
	// Will call quit to free up SDL. May change in the future
	void Start();
	void Quit();


};

