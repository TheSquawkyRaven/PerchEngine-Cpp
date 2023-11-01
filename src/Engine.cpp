#include "Engine.h"

#include "Log.h"

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

bool Engine::InitializeMainWindow()
{
	// Initialize SDL Video Graphics
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Log::Errorf("Could not initialize SDL_VIDEO! SDL_ERROR: %s", SDL_GetError());
		return false;
	}

	// InitializeMainWindow a main window
	// Title, X, & Y pos of window position on screen, width, height, show window when created
	MainWindow = SDL_CreateWindow("SDL Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
	if (MainWindow == NULL)
	{
		Log::Errorf("Window cannot be created! SDL_ERROR: %s", SDL_GetError());
		return false;
	}

	MainWindowSurface = SDL_GetWindowSurface(MainWindow);
	SDL_FillRect(MainWindowSurface, NULL, SDL_MapRGB(MainWindowSurface->format, 0xff, 0xff, 0xff));

	SDL_UpdateWindowSurface(MainWindow);


	return true;
}

void Engine::Start()
{
	SDL_Event e;
	bool quit = false;
	while (quit == false)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}

	Quit();
}

void Engine::Quit()
{
	SDL_DestroyWindow(MainWindow);

	SDL_Quit();
}
