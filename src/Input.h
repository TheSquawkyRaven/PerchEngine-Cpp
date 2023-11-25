#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


// Main SDL Window
#include <SDL.h>


namespace Perch
{

	// For bool return functions, true represents success
	class Input
	{

		// # Variables + Getters/Setters

	private:

		Uint8* KeyboardStates = NULL;

	public:



		// ###


		// # Functions

	private:


	public:

		void UpdateInput(SDL_Event* e, bool* quit);

		PERCHENGINECPP_API bool GetKey(SDL_Scancode sdlScancode);

		// ###
	};
}