#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


// Main SDL Window
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "EngineComponents/Input.h"
#include "EngineComponents/Random.h"

#include "Structs/Vector2.h"
#include "Structs/Vector2i.h"
#include "Structs/Rect2.h"
#include "Structs/Viewport.h"
#include "Structs/Color.h"

#include <string>
#include <functional>
#include <memory>
#include <stack>
#include <unordered_set>


namespace Perch
{

	class Script;
	class Collider2D;

	// Config definition
	class EngineConfig
	{

	public:

		std::string WindowName = "";
		Vector2i WindowSize = Vector2i(640, 480);

		Color ClearColor = Color();

		bool ShowDebug = false;

	};

	// Engine is a friend of Branch
	class Branch;

	// For bool return functions, true represents success
	class Engine
	{

		// # Variables + Getters/Setters

	private:

		std::shared_ptr<EngineConfig> Config;
		Rect2 MainWindowRect = Rect2();

		bool HasError = false;

		// SDL Window for rendering into
		SDL_Window* MainWindow = nullptr;

		// SDL Renderer for hardware rendering
		SDL_Renderer* MainWindowRenderer = nullptr;

		// Root is not deleted when deconstructing because the destroy function will delete itself!
		std::unique_ptr<Branch> Root = nullptr;

		std::function<void(Engine* Engine, Branch* Root)> OnRootCreate = NULL;

		std::unique_ptr<Viewport> RootViewport = std::unique_ptr<Viewport>(new Viewport(MainWindowRect));
		std::stack<Viewport*> ViewportStack;

		Uint32 LastUpdateTicks = 0;

		std::unique_ptr<Input> InputRef = std::unique_ptr<Input>(new Input);
		std::unique_ptr<Random> RandomRef = std::unique_ptr<Random>(new Random);

	public:

		PERCH_API inline Rect2 GetMainWindowRect() const { return MainWindowRect; }
		PERCH_API inline Vector2 GetMainWindowSize() { return MainWindowRect.GetSize(); }
		PERCH_API inline bool DoShowDebug() { return Config->ShowDebug; }
		PERCH_API inline SDL_Renderer* GetMainWindowRenderer() { return MainWindowRenderer; }
		PERCH_API inline Input* GetInput() const { return InputRef.get(); }
		PERCH_API inline Random* GetRandom() const { return RandomRef.get(); }

	public:

		float DeltaTime = 0.0f;
		float TotalTime = 0.0f;

		// TODO Move to 2D Physics class
		std::unordered_set<Collider2D*> ColliderStack;

		// ###


		// # Functions

	private:

		// Init - Runs in a constructor level
		bool InitMainWindow();

		// Create - 
		void CreateTree();
		void RunTree();

		// Update - Runs every frame
		void Update(std::shared_ptr<SDL_Event> e, bool* quit);
		void StartUpdateLoop();

		void UpdateTime();

		// Returns true if has error
		bool CheckError() const;

	public:

		PERCH_API Engine(std::shared_ptr<EngineConfig> config);
		PERCH_API void UpdateConfig();

		PERCH_API inline void SetOnRootCreate(std::function<void(Engine* Engine, Branch* Root)> onRootCreate) { this->OnRootCreate = onRootCreate; };

		// Simulate viewport use, called in update when it is not drawing for children to use viewport data
		PERCH_API void SimulateUseViewport(Viewport* viewport);
		PERCH_API void SimulateUnuseViewport(Viewport* viewport);

		// Called in Draw and DrawOut to set the current viewport
		PERCH_API void UseViewport(SDL_Renderer* renderer, Viewport* viewport);
		PERCH_API void UnuseViewport(SDL_Renderer* renderer, Viewport* viewport);

		PERCH_API Viewport* GetCurrentViewport();
		PERCH_API void ClearViewportStack();

		// "Start" here will wait for until the closure of the MainWindow
		// Will call quit to free up SDL. May change in the future
		PERCH_API void Start();
		PERCH_API void Quit();

		// ###
	};
}
