#include "Engine.h"

#include "Log.h"

using namespace Perch;
using namespace Squawk;

void Engine::SetScreenWidth(int width)
{
	ScreenWidth = width;
}

void Engine::SetScreenHeight(int height)
{
	ScreenHeight = height;
}

void Engine::Update(SDL_Event* e, bool* quit)
{
	// Check for input events
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_QUIT)
		{
			*quit = true;
		}
	}

	// Update frame
	SDL_UpdateWindowSurface(MainWindow);
}

void Perch::Engine::StartUpdateLoop()
{
	SDL_Event* e = new SDL_Event{};
	bool quit = false;
	do
	{
		Update(e, &quit);

	} while (!quit);

	delete e;
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
	// Title, X, & Y pos of window position on screen, width, height, hide window when created
	MainWindow = SDL_CreateWindow("SDL Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_HIDDEN);
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

SDL_Surface* Engine::LoadBmpSurface(std::string path)
{
	SDL_Surface* rawSurface = SDL_LoadBMP(path.c_str());
	if (rawSurface == NULL)
	{
		Log::Errorf("Failed to load bmp texture! SDL_ERROR: %s", SDL_GetError());
		return NULL;
	}

	// Optimize
	// Bmp textures are generally 24 bit. This pre-converts the texture to 32 bit (or monitor's bits, in this case the MainWindow's Surface)
	// so SDL won't have to convert 24 bit -> 32 bit every time it is blitted
	SDL_Surface* optimizedSurface = SDL_ConvertSurface(rawSurface, MainWindowSurface->format, 0);
	if (optimizedSurface == NULL)
	{
		Log::Errorf("Failed to optimize bmp texture! SDL_ERROR: %s", SDL_GetError());
		return NULL;
	}

	// Since Converting it creates a new copy, free the raw bmp texture
	SDL_FreeSurface(rawSurface);

	return optimizedSurface;
}

void Engine::BlitSurface(SDL_Surface* surface)
{
	SDL_BlitSurface(surface, NULL, MainWindowSurface, NULL);
}

void Engine::BlitSurfaceScaled(SDL_Surface* surface)
{
	SDL_Rect scaleRect{};
	scaleRect.x = 0;
	scaleRect.y = 0;
	scaleRect.w = ScreenWidth;
	scaleRect.h = ScreenHeight;

	SDL_BlitScaled(surface, NULL, MainWindowSurface, &scaleRect);
}

void Engine::Start()
{
	SDL_ShowWindow(MainWindow);
	
	StartUpdateLoop();

	Quit();
}

void Engine::Quit()
{
	SDL_FreeSurface(BmpSurface);
	BmpSurface = NULL;

	SDL_DestroyWindow(MainWindow);
	MainWindow = NULL;

	SDL_Quit();

	Log::Print("MainWindow is Closed");
}
