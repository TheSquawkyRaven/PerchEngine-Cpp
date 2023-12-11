#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


// Main SDL Window
#include <SDL.h>

#include "../Structs/Vector2i.h"

#include <memory>

namespace Perch
{

	class Input
	{

	public:
		enum MouseEvent
		{
			NONE = 0,
			DOWN = 1,
			UP = 2,
			HELD = 3,
		};

		enum MouseButton
		{
			LEFT = 0,
			MIDDLE = 1,
			RIGHT = 2,
			X1 = 3,
			X2 = 4,
		};

		// # Variables + Getters/Setters

	private:

		Uint8* lastKeyboardStates = new Uint8[SDL_NUM_SCANCODES];
		Uint8* keyboardStates = nullptr;

		MouseEvent* mouseStates = new MouseEvent[5];

		Vector2i mousePosition = Vector2i();
		int mouseScrollX = 0;
		int mouseScrollY = 0;

	public:

		inline Vector2i GetMousePosition() const { return mousePosition; }
		inline int GetMouseScrollX() const { return mouseScrollX; }
		inline int GetMouseScrollY() const { return mouseScrollY; }


		// ###


		// # Functions

	private:

		void UpdateKeyboardStates();

		void ResetMouseStates();
		int GetMouseButtonIndex(Uint8 button);
		void UpdateMouseState(SDL_MouseButtonEvent mouseButtonEvent, MouseEvent mouseEvent);

	public:

		void UpdateInput(SDL_Event* e, bool* quit);

		PERCH_API bool GetKey(SDL_Scancode sdlScancode);
		PERCH_API bool GetKeyDown(SDL_Scancode sdlScancode);
		PERCH_API bool GetKeyUp(SDL_Scancode sdlScancode);

		PERCH_API bool GetMouse(MouseButton button);
		PERCH_API bool GetMouseDown(MouseButton button);
		PERCH_API bool GetMouseUp(MouseButton button);

		// ###
	};
}
