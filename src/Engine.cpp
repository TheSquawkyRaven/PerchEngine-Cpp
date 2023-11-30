#include "pch.h"

#include "Engine.h"

#include "Squawk/Log.h"
#include "Branch/Branch.h"
#include <cassert>

using namespace std;
using namespace Perch;
using namespace Squawk;

void Engine::Update(SDL_Event* e, bool* quit)
{
	input->UpdateInput(e, quit);

	UpdateTime();
	root->_Update();
	root->_UpdateOut();

	root->_PhysicsUpdate();

	root->_CollisionUpdate();
	colliderStack.clear();	// TODO move to Physics2D function

	Color c = config->clearColor;
	SDL_SetRenderDrawColor(mainWindowRenderer, c.r, c.g, c.b, c.a);
	SDL_RenderClear(mainWindowRenderer);

	// Update branch destruction before drawing
	UpdateBranchDestruction();
	UseViewport(mainWindowRenderer, rootViewport.get());
	root->_Draw(mainWindowRenderer);
	root->_DrawOut(mainWindowRenderer);
	UnuseViewport(mainWindowRenderer, rootViewport.get());
	ClearViewportStack();

	SDL_RenderPresent(mainWindowRenderer);

	if (doQuit)
	{
		*quit = true;
	}
}

void Engine::StartUpdateLoop()
{
	shared_ptr<SDL_Event> e = shared_ptr<SDL_Event>(new SDL_Event);
	bool quit = false;
	do
	{
		Update(e.get(), &quit);

	} while (!quit);

}

void Engine::UpdateTime()
{
	Uint64 currentTicks = SDL_GetTicks64();
	Uint64 elapsedTicks = currentTicks - lastUpdateTicks;
	
	realDeltaTime = elapsedTicks / 1000.0f;
	realTotalTime = currentTicks / 1000.0f;

	deltaTime = realDeltaTime * timeScale;
	totalTime += deltaTime;

	lastUpdateTicks = currentTicks;
}

void Engine::AddBranchToDestructionQueue(Branch* branch)
{
	destructionQueue.push(branch);
}

void Engine::UpdateBranchDestruction()
{
	while (!destructionQueue.empty())
	{
		Branch* branch = destructionQueue.front();
		destructionQueue.pop();
		branch->_Destroy(false);
	}
}

bool Engine::InitMainWindow()
{
	// Create SDL Video Graphics
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		Log::Errorf("Could not initialize SDL_VIDEO or SDL_AUDIO! SDL_ERROR: %s", SDL_GetError());
		return false;
	}

	// Create a main window
	// Title, X, & Y pos of window position on screen, width, height, hide window when created
	Vector2i ScreenSize = GetMainWindowSize();
	mainWindow = SDL_CreateWindow(config->windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenSize.x, ScreenSize.y, SDL_WINDOW_HIDDEN);
	if (mainWindow == nullptr)
	{
		Log::Errorf("Window cannot be created! SDL_ERROR: %s", SDL_GetError());
		return false;
	}

	// Hardware Accelerated renderer with VSync
	mainWindowRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mainWindowRenderer == nullptr)
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

	// Mixer (Audio) Loading
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		Log::Errorf("SDL_mixer cannot initialize! SDL_MIXER_ERROR: %s", Mix_GetError());
		return false;
	}

	// TTF Loading
	if (TTF_Init() == -1)
	{
		Log::Errorf("SDL_TTF cannot initialize! SDL_TTF_ERROR: %s", TTF_GetError());
		return false;
	}

	// Renderer settings
	Color c = config->clearColor;
	SDL_SetRenderDrawBlendMode(mainWindowRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(mainWindowRenderer, c.r, c.g, c.b, c.a);
	SDL_RenderClear(mainWindowRenderer);

	return true;
}

// Creates the root branch and calls the delegate for OnRootCreate for attachments of branches
void Engine::CreateTree()
{
	root = unique_ptr<Branch>(new Branch(this));

	if (onRootCreate == nullptr)
	{
		Log::Warn("onRootCreate is not set, no root will be attached!");
		return;
	}
	onRootCreate(this, root.get());
}

// Calls ready from the root
void Engine::RunTree()
{
	if (CheckError())
	{
		return;
	}

	root->_Ready();
}

bool Engine::CheckError() const
{
	if (hasError)
	{
		Log::Error("Engine has error, please refer to log");
		return true;
	}
	return false;
}

void Engine::QuitEngine()
{
	root->Destroy();

	SDL_DestroyRenderer(mainWindowRenderer);
	SDL_DestroyWindow(mainWindow);

	mainWindow = nullptr;
	mainWindowRenderer = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	Log::Print("Main Window is Closed");
}

Engine::Engine(shared_ptr<EngineConfig> config)
{
	this->config = config;
	UpdateConfig();

	bool success = InitMainWindow();
	if (!success)
	{
		hasError = true;
	}

}

void Engine::UpdateConfig()
{
	mainWindowRect.SetSize(config->windowSize);
	rootViewport->rect = mainWindowRect;
}

void Engine::SimulateUseViewport(Viewport* viewport)
{
	viewportStack.push(viewport);
}

void Engine::SimulateUnuseViewport(Viewport* viewport)
{
	Viewport* viewportCheck = viewportStack.top();
	if (viewportCheck != viewport)
	{
		Log::Error("Viewport Stack is not properly popped (SimulateUnuseViewport)!");
	}
	viewportStack.pop();
}

void Engine::UseViewport(SDL_Renderer* renderer, Viewport* viewport)
{
	viewportStack.push(viewport);
	SDL_RenderSetViewport(renderer, viewport->GetSDLRect().get());
}

void Engine::UnuseViewport(SDL_Renderer* renderer, Viewport* viewport)
{
	Viewport* viewportCheck = viewportStack.top();
	if (viewportCheck != viewport)
	{
		Log::Errorf("Viewport Stack is not properly popped (UnuseViewport)! (%p == %p)", viewportCheck, viewport);
	}
	viewportStack.pop();
	if (viewportStack.empty())
	{
		return;
	}
	Viewport* currentViewport = viewportStack.top();
	SDL_RenderSetViewport(renderer, currentViewport->GetSDLRect().get());
}

Viewport* Engine::GetCurrentViewport()
{
	return viewportStack.top();
}

void Engine::ClearViewportStack()
{
	while (!viewportStack.empty())
	{
		viewportStack.pop();
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

	SDL_ShowWindow(mainWindow);
	
	StartUpdateLoop();

	QuitEngine();
}

void Engine::Quit()
{
	doQuit = true;
}
