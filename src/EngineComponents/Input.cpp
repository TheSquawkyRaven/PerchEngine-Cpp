#include "pch.h"

#include "Input.h"

#include "../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

void Input::UpdateKeyboardStates()
{
	if (keyboardStates == nullptr)
	{
		return;
	}
	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		lastKeyboardStates[i] = keyboardStates[i];
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

	keyboardStates = (Uint8*)SDL_GetKeyboardState(nullptr);
}

bool Input::GetKey(SDL_Scancode sdlScancode)
{
	return keyboardStates[sdlScancode];
}

bool Input::GetKeyDown(SDL_Scancode sdlScancode)
{
	return !lastKeyboardStates[sdlScancode] && keyboardStates[sdlScancode];
}

bool Input::GetKeyUp(SDL_Scancode sdlScancode)
{
	return lastKeyboardStates[sdlScancode] && !keyboardStates[sdlScancode];
}
