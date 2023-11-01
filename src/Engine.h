#pragma once

// Main SDL Window
#include <SDL.h>

#include <string>

namespace Perch
{

	// For bool return functions, true represents success
	class Engine
	{

		class Branch;

		// # Variables + Getters/Setters

	private:

		int ScreenWidth;
		int ScreenHeight;

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

	public:

		SDL_Surface* BmpSurface = NULL;

		// ###


		// # Functions

	private:

		void Update(SDL_Event* e, bool* quit);
		void StartUpdateLoop();

	public:

		Engine(int ScreenWidth = 480, int ScreenHeight = 640);

		bool InitializeMainWindow();

		SDL_Surface* LoadBmpSurface(std::string path);

		void BlitSurface(SDL_Surface* surface);
		void BlitSurfaceScaled(SDL_Surface* surface);

		// "Start" here will wait for until the closure of the MainWindow
		// Will call quit to free up SDL. May change in the future
		void Start();
		void Quit();

		// ###

	};

}
