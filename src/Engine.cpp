#include "pch.h"

#include "Engine.h"

#include "Log.h"
#include "Branch/Branch.h"
#include <cassert>

using namespace std;
using namespace Perch;
using namespace Squawk;

void Engine::Update(SDL_Event* e, bool* quit)
{
	InputRef->UpdateInput(e, quit);

	UpdateTime();
	Root->_Update();
	Root->_UpdateOut();

	Root->_PhysicsUpdate();

	Root->_CollisionUpdate();
	ColliderStack.clear();	// TODO move to Physics2D function

	Color c = Config->ClearColor;
	SDL_SetRenderDrawColor(MainWindowRenderer, c.R, c.G, c.B, c.A);
	SDL_RenderClear(MainWindowRenderer);

	UseViewport(MainWindowRenderer, RootViewport);
	Root->_Draw(MainWindowRenderer);
	Root->_DrawOut(MainWindowRenderer);
	UnuseViewport(MainWindowRenderer, RootViewport);
	ClearViewportStack();

	SDL_RenderPresent(MainWindowRenderer);
}

void Engine::StartUpdateLoop()
{
	SDL_Event* e = new SDL_Event{};
	bool quit = false;
	do
	{
		Update(e, &quit);

	} while (!quit);

	delete e;
}

void Engine::UpdateTime()
{
	Uint32 currentTicks = SDL_GetTicks();
	Uint32 elapsedTicks = currentTicks - LastUpdateTicks;
	
	DeltaTime = elapsedTicks / 1000.0f;
	TotalTime = currentTicks / 1000.0f;

	LastUpdateTicks = currentTicks;
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
	Vector2i ScreenSize = GetMainWindowSize();
	MainWindow = SDL_CreateWindow(Config->WindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenSize.X, ScreenSize.Y, SDL_WINDOW_HIDDEN);
	if (MainWindow == NULL)
	{
		Log::Errorf("Window cannot be created! SDL_ERROR: %s", SDL_GetError());
		return false;
	}

	// Hardware Accelerated renderer with VSync
	MainWindowRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (MainWindowRenderer == NULL)
	{
		Log::Errorf("Renderer cannot be created! SDL_ERROR: %s", SDL_GetError());
		return false;
	}

	// PNG Loading
	// Attempt to initialize the PNG Loader
	int imageFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imageFlags) & imageFlags))
	{
		Log::Errorf("SDL_image cannot initialize! SDL_IMAGE_ERROR: %s", IMG_GetError());
		return false;
	}

	// TTF Loading
	if (TTF_Init() == -1)
	{
		Log::Errorf("SDL_TTF cannot initialize! SDL_TTF_ERROR: %s", TTF_GetError());
		return false;
	}

	// Renderer color
	Color c = Config->ClearColor;
	SDL_SetRenderDrawColor(MainWindowRenderer, c.R, c.G, c.B, c.A);
	SDL_RenderClear(MainWindowRenderer);


	return true;
}

// Creates the root branch and calls the delegate for OnRootCreate for attachments of branches
void Engine::CreateTree()
{
	Root = new Branch(this);

	if (OnRootCreate == NULL)
	{
		Log::Warn("OnRootCreate is not set, no root will be attached!");
		return;
	}
	OnRootCreate(this, Root);
}

// Calls ready from the root
void Engine::RunTree()
{
	if (CheckError())
	{
		return;
	}

	Root->_Ready();
}

bool Engine::CheckError() const
{
	if (HasError)
	{
		Log::Error("Engine has error, please refer to log");
		return true;
	}
	return false;
}

Engine::Engine(shared_ptr<EngineConfig> config)
{
	Config = config;
	UpdateConfig();

	bool success = InitMainWindow();
	if (!success)
	{
		HasError = true;
	}

}

void Engine::UpdateConfig()
{
	MainWindowRect.SetSize(Config->WindowSize);
	RootViewport->Rect = MainWindowRect;
}

void Engine::SimulateUseViewport(shared_ptr<Viewport> viewport)
{
	ViewportStack.push(viewport);
}

void Engine::SimulateUnuseViewport(shared_ptr<Viewport> viewport)
{
	shared_ptr<Viewport> viewportCheck = ViewportStack.top();
	if (viewportCheck != viewport)
	{
		Log::Error("Viewport Stack is not properly popped (SimulateUnuseViewport)!");
	}
	ViewportStack.pop();
}

void Engine::UseViewport(SDL_Renderer* renderer, shared_ptr<Viewport> viewport)
{
	ViewportStack.push(viewport);
	SDL_RenderSetViewport(renderer, viewport->GetSDLRect().get());
}

void Engine::UnuseViewport(SDL_Renderer* renderer, std::shared_ptr<Viewport> viewport)
{
	shared_ptr<Viewport> viewportCheck = ViewportStack.top();
	if (viewportCheck != viewport)
	{
		Log::Errorf("Viewport Stack is not properly popped (UnuseViewport)! (%p == %p)", viewportCheck, viewport);
	}
	ViewportStack.pop();
	if (ViewportStack.empty())
	{
		return;
	}
	shared_ptr<Viewport> currentViewport = ViewportStack.top();
	SDL_RenderSetViewport(renderer, currentViewport->GetSDLRect().get());
}

shared_ptr<Viewport> Engine::GetCurrentViewport()
{
	return ViewportStack.top();
}

void Engine::ClearViewportStack()
{
	while (!ViewportStack.empty())
	{
		ViewportStack.pop();
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

	MainWindow = NULL;
	MainWindowRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	Log::Print("MainWindow is Closed");
}
