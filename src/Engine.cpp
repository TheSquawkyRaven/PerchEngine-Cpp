#include "Engine.h"

#include "Log.h"
#include "Branch/Branch.h"

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

bool Engine::CreateMainWindow()
{
	// Create SDL Video Graphics
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Log::Errorf("Could not initialize SDL_VIDEO! SDL_ERROR: %s", SDL_GetError());
		return false;
	}

	// Create a main window
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

bool Engine::CreateTree()
{
	Root = new Branch();

	if (OnRootCreate == NULL)
	{
		Log::Warn("OnRootCreate is not set, no root will be attached!");
		return true;
	}
	(*OnRootCreate)(Root);

	return true;
}

bool Perch::Engine::CheckError()
{
	if (HasError)
	{
		Log::Error("Engine has error, please refer to log");
		return true;
	}
	return false;
}

Engine::Engine(int ScreenHeight, int ScreenWidth)
{
	this->ScreenWidth = ScreenWidth;
	this->ScreenHeight = ScreenHeight;

	bool success = CreateMainWindow();
	if (!success)
	{
		HasError = true;
	}
}

bool Perch::Engine::Create()
{
	if (CheckError())
	{
		return NULL;
	}

	bool success = CreateTree();
	if (!success)
	{
		return NULL;
	}
	return true;
}

void Perch::Engine::Run()
{
	if (CheckError())
	{
		return;
	}

	Root->Init();
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
	if (CheckError())
	{
		return;
	}

	SDL_ShowWindow(MainWindow);
	
	StartUpdateLoop();

	Quit();
}

void Engine::Quit()
{
	SDL_DestroyWindow(MainWindow);
	MainWindow = NULL;

	SDL_Quit();

	Log::Print("MainWindow is Closed");
}
