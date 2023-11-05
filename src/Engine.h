#pragma once

// Main SDL Window
#include <SDL.h>

#include <string>
#include <functional>

namespace Perch
{

	// Engine is a friend of Branch
	class Branch;

	// For bool return functions, true represents success
	class Engine
	{

		// # Variables + Getters/Setters

	private:

		int ScreenWidth;
		int ScreenHeight;

		bool HasError = false;

	public:

		void SetScreenWidth(int width);
		void SetScreenHeight(int height);

		inline int GetScreenWidth() { return ScreenWidth; }
		inline int GetScreenHeight() { return ScreenHeight; }

	private:

		// SDL Window for rendering into
		SDL_Window* MainWindow = NULL;

		// Retrieved from MainWindow, the surface (texture) of the SDL_Window
		SDL_Surface* MainWindowSurface = NULL;

		Branch* Root = NULL;

		std::function<void(Branch* Root)>* OnRootCreate = NULL;

	public:
		inline SDL_Surface* GetMainWindowSurface() { return MainWindowSurface; }

		// ###


		// # Functions

	private:

		void Update(SDL_Event* e, bool* quit);
		void StartUpdateLoop();

		bool CreateMainWindow();
		bool CreateTree();

		// Returns true if has error
		bool CheckError();

	public:

		Engine(int ScreenWidth = 480, int ScreenHeight = 640);

		inline void SetOnRootCreate(std::function<void(Branch* Root)>* onRootCreate) { this->OnRootCreate = onRootCreate; };

		bool Create();
		void Run();

		void BlitSurface(SDL_Surface* surface);
		void BlitSurfaceScaled(SDL_Surface* surface);

		// "Start" here will wait for until the closure of the MainWindow
		// Will call quit to free up SDL. May change in the future
		void Start();
		void Quit();

		// ###

	};

}
