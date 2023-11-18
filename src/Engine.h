#pragma once

// Main SDL Window
#include <SDL.h>
#include <SDL_image.h>

#include "Structs/Vector2.h"
#include "Structs/Vector2i.h"
#include "Structs/Rect2.h"

#include <string>
#include <functional>
#include <memory>


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
		bool HasError = false;

	public:

		inline void SetScreenSize(Vector2i size) { Config->WindowSize = size; }
		inline Vector2i GetScreenSize() { return Config->WindowSize; }
		inline Rect2 GetScreenRect() { return Rect2(0, 0, Config->WindowSize.X, Config->WindowSize.Y); }

	private:

		// SDL Window for rendering into
		SDL_Window* MainWindow = NULL;

		// SDL Renderer for hardware rendering
		SDL_Renderer* MainWindowRenderer = NULL;

		// Deprecate
		// Retrieved from MainWindow, the surface (texture) of the SDL_Window
		SDL_Surface* MainWindowSurface = NULL;

		Branch* Root = NULL;

		std::function<void(Engine* Engine, Branch* Root)> OnRootCreate = NULL;

	public:

		inline SDL_Renderer* GetMainWindowRenderer() { return MainWindowRenderer; }
		inline SDL_Surface* GetMainWindowSurface() { return MainWindowSurface; }

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

		inline void SetOnRootCreate(std::function<void(Engine* Engine, Branch* Root)> onRootCreate) { this->OnRootCreate = onRootCreate; };

		template<typename BranchT>
		static inline std::shared_ptr<BranchT> CreateBranch()
		{
			static_assert(std::is_base_of<Branch, BranchT>::value, "CreateBranch template must be derived from Branch.");
			BranchT* branch = new BranchT();
			branch->_Init();
			return std::shared_ptr<BranchT>(branch);
		}

		// "Start" here will wait for until the closure of the MainWindow
		// Will call quit to free up SDL. May change in the future
		void Start();
		void Quit();

		// ###
	};
}
