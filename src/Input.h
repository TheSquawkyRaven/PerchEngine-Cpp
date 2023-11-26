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

	class Input
	{

		// # Variables + Getters/Setters

	private:

		Uint8* LastKeyboardStates = new Uint8[SDL_NUM_SCANCODES];
		Uint8* KeyboardStates = NULL;

	public:

		// ###


		// # Functions

	private:

		void UpdateKeyboardStates();

	public:

		void UpdateInput(SDL_Event* e, bool* quit);

		PERCHENGINECPP_API bool GetKey(SDL_Scancode sdlScancode);
		PERCHENGINECPP_API bool GetKeyDown(SDL_Scancode sdlScancode);
		PERCHENGINECPP_API bool GetKeyUp(SDL_Scancode sdlScancode);

		// ###
	};
}
