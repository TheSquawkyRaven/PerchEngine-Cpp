#pragma once

// Main SDL Window
#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <functional>
#include "Structs/Vector2.h"


namespace Perch
{

	// Config definition
	class EngineConfig
	{

	public:

		std::string WindowName = "";
		Vector2 WindowSize = Vector2(640, 480);
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

		inline void SetScreenSize(Vector2 size) { Config->WindowSize = size; }
		inline Vector2 GetScreenSize() { return Config->WindowSize; }

	private:

		// SDL Window for rendering into
		SDL_Window* MainWindow = NULL;

		// Retrieved from MainWindow, the surface (texture) of the SDL_Window
		SDL_Surface* MainWindowSurface = NULL;

		Branch* Root = NULL;

		std::function<void(Engine* Engine, Branch* Root)> OnRootCreate = NULL;

	public:
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
		static inline BranchT* CreateBranch()
		{
			static_assert(std::is_base_of<Branch, BranchT>::value, "CreateBranch template must be derived from Branch.");
			BranchT* branch = new BranchT();
			branch->_Init();
			return branch;
		}

		// "Start" here will wait for until the closure of the MainWindow
		// Will call quit to free up SDL. May change in the future
		void Start();
		void Quit();

		// ###
	};
}
