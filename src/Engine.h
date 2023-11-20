#pragma once

// Main SDL Window
#include <SDL.h>
#include <SDL_image.h>

#include "Structs/Vector2.h"
#include "Structs/Vector2i.h"
#include "Structs/Rect2.h"
#include "Structs/Viewport.h"

#include <string>
#include <functional>
#include <memory>
#include <stack>


namespace Perch
{

	// Config definition
	class EngineConfig
	{

	public:

		std::string WindowName = "";
		Vector2i WindowSize = Vector2i(640, 480);
		bool SupportPNGLoading = true;

	};

	// Engine is a friend of Branch
	class Branch;

	// For bool return functions, true represents success
	class Engine
	{

		// # Variables + Getters/Setters

	private:

		EngineConfig* Config;
		Rect2 MainWindowRect = Rect2();

		bool HasError = false;

		// SDL Window for rendering into
		SDL_Window* MainWindow = NULL;

		// SDL Renderer for hardware rendering
		SDL_Renderer* MainWindowRenderer = NULL;

		Branch* Root = NULL;

		std::function<void(Engine* Engine, Branch* Root)> OnRootCreate = NULL;

		std::shared_ptr<Viewport> RootViewport = std::shared_ptr<Viewport>(new Viewport(&MainWindowRect));
		std::stack<std::shared_ptr<Viewport>> ViewportStack;

	public:

		inline Rect2 GetMainWindowRect() const { return MainWindowRect; }
		inline SDL_Renderer* GetMainWindowRenderer() { return MainWindowRenderer; }

		// ###


		// # Functions

	private:

		// Init - Runs in a constructor level
		bool InitMainWindow();

		// Create - 
		void CreateTree();
		void RunTree();

		// Update - Runs every frame
		void Update(SDL_Event* e, bool* quit);
		void StartUpdateLoop();

		// Returns true if has error
		bool CheckError() const;

	public:

		Engine(EngineConfig* config);
		void UpdateConfig();

		inline void SetOnRootCreate(std::function<void(Engine* Engine, Branch* Root)> onRootCreate) { this->OnRootCreate = onRootCreate; };

		// Simulate viewport use, called in update when it is not drawing for children to use viewport data
		void SimulateUseViewport(std::shared_ptr<Viewport> viewport);
		void SimulateUnuseViewport(std::shared_ptr<Viewport> viewport);

		// Called in Draw and DrawOut to set the current viewport
		void UseViewport(SDL_Renderer* renderer, std::shared_ptr<Viewport> viewport);
		void UnuseViewport(SDL_Renderer* renderer, std::shared_ptr<Viewport> viewport);

		std::shared_ptr<Viewport> GetCurrentViewport();
		void ClearViewportStack();

		template<typename BranchT>
		inline std::shared_ptr<BranchT> CreateBranch()
		{
			static_assert(std::is_base_of<Branch, BranchT>::value, "CreateBranch template must be derived from Branch.");
			BranchT* branch = new BranchT();
			branch->_Init(this);
			return std::shared_ptr<BranchT>(branch);
		}

		// "Start" here will wait for until the closure of the MainWindow
		// Will call quit to free up SDL. May change in the future
		void Start();
		void Quit();

		// ###
	};
}
