#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


// Main SDL Window
#include <SDL.h>

#include <memory>

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

		void UpdateInput(std::shared_ptr<SDL_Event> e, bool* quit);

		PERCH_API bool GetKey(SDL_Scancode sdlScancode);
		PERCH_API bool GetKeyDown(SDL_Scancode sdlScancode);
		PERCH_API bool GetKeyUp(SDL_Scancode sdlScancode);

		// ###
	};
}
