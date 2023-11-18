#include "Engine.h"

#include "Log.h"
#include "Branch/Branch.h"

using namespace Perch;
using namespace Squawk;

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

	Root->_Update();

	// How to use this to return to previous viewport rect when going out of drawing of the parent viewport?
	SDL_Rect* screenSDLRect = GetScreenRect().GetSDLRect();
	SDL_RenderSetViewport(MainWindowRenderer, screenSDLRect);

	SDL_SetRenderDrawColor(MainWindowRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(MainWindowRenderer);

	Root->_Draw(MainWindowRenderer);

	SDL_RenderPresent(MainWindowRenderer);

	delete screenSDLRect;
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

bool Engine::InitMainWindow()
{
	// Create SDL Video Graphics
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Log::Errorf("Could not initialize SDL_VIDEO! SDL_ERROR: %s", SDL_GetError());
		return false;
	}

	// Create a main window
	// Title, X, & Y pos of window position on screen, width, height, hide window when created
	Vector2i ScreenSize = GetScreenSize();
	MainWindow = SDL_CreateWindow("SDL Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenSize.X, ScreenSize.Y, SDL_WINDOW_HIDDEN);
	if (MainWindow == NULL)
	{
		Log::Errorf("Window cannot be created! SDL_ERROR: %s", SDL_GetError());
		return false;
	}

	MainWindowRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (MainWindowRenderer == NULL)
	{
		Log::Errorf("Renderer cannot be created! SDL_ERROR: %s", SDL_GetError());
		return false;
	}
	// Renderer color
	SDL_SetRenderDrawColor(MainWindowRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// PNG Loading
	if (Config->SupportPNGLoading)
	{
		// Attempt to initialize the PNG Loader
		int imageFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imageFlags) & imageFlags))
		{
			Log::Errorf("SDL_image cannot initialize! SDL_IMAGE_ERROR: %s", IMG_GetError());
			return false;
		}
	}

	SDL_RenderClear(MainWindowRenderer);


	return true;
}

// Creates the root branch and calls the delegate for OnRootCreate for attachments of branches
void Engine::CreateTree()
{
	Root = new Branch();

	if (OnRootCreate == NULL)
	{
		Log::Warn("OnRootCreate is not set, no root will be attached!");
		return;
	}
	OnRootCreate(this, Root);
}

// Calls ready from the root
void Perch::Engine::RunTree()
{
	if (CheckError())
	{
		return;
	}

	Root->_Ready();
}

bool Perch::Engine::CheckError() const
{
	if (HasError)
	{
		Log::Error("Engine has error, please refer to log");
		return true;
	}
	return false;
}

Engine::Engine(EngineConfig* config)
{
	Config = config;

	bool success = InitMainWindow();
	if (!success)
	{
		HasError = true;
	}
}

void Engine::Start()
{
	if (CheckError())
	{
		return;
	}

	CreateTree();

	RunTree();

	SDL_ShowWindow(MainWindow);
	
	StartUpdateLoop();

	Quit();
}

void Engine::Quit()
{
	// Destroy Texture
	// SDL_DestroyTexture(texture);

	Root->Destroy();

	SDL_DestroyRenderer(MainWindowRenderer);
	SDL_DestroyWindow(MainWindow);

	MainWindowRenderer = NULL;
	MainWindow = NULL;

	IMG_Quit();
	SDL_Quit();

	Log::Print("MainWindow is Closed");
}
