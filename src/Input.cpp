#include "pch.h"

#include "Input.h"

#include "Log.h"
#include "Branch/Branch.h"
#include <cassert>

using namespace std;
using namespace Perch;
using namespace Squawk;

void Input::UpdateInput(SDL_Event* e, bool* quit)
{
	while (SDL_PollEvent(e))
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
