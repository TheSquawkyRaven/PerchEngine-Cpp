#include "pch.h"

#include "Input.h"

#include "../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

void Input::UpdateKeyboardStates()
{
	if (KeyboardStates == NULL)
	{
		return;
	}
	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		LastKeyboardStates[i] = KeyboardStates[i];
	}
}

void Input::UpdateInput(shared_ptr<SDL_Event> e, bool* quit)
{
	UpdateKeyboardStates();

	while (SDL_PollEvent(e.get()))
	{
		if (e->type == SDL_QUIT)
		{
			*quit = true;
		}
	}

	KeyboardStates = (Uint8*)SDL_GetKeyboardState(NULL);
}

bool Input::GetKey(SDL_Scancode sdlScancode)
{
	return KeyboardStates[sdlScancode];
}

bool Input::GetKeyDown(SDL_Scancode sdlScancode)
{
	return !LastKeyboardStates[sdlScancode] && KeyboardStates[sdlScancode];
}

bool Input::GetKeyUp(SDL_Scancode sdlScancode)
{
	return LastKeyboardStates[sdlScancode] && !KeyboardStates[sdlScancode];
}
