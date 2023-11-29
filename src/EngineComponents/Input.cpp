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

void Input::ResetMouseStates()
{
	for (int i = 0; i < 5; i++)
	{
		if (mouseStates[i] == HELD)
		{
			continue;
		}
		if (mouseStates[i] == DOWN)
		{
			mouseStates[i] = HELD;
			continue;
		}
		mouseStates[i] = NONE;
	}
	mouseScrollX = 0;
	mouseScrollY = 0;
}

int Input::GetMouseButtonIndex(Uint8 button)
{
	switch (button)
	{
	case SDL_BUTTON_LEFT:
		return LEFT;
	case SDL_BUTTON_MIDDLE:
		return MIDDLE;
	case SDL_BUTTON_RIGHT:
		return RIGHT;
	case SDL_BUTTON_X1:
		return X1;
	case SDL_BUTTON_X2:
		return X2;
	}
	return -1;
}

void Input::UpdateMouseState(SDL_MouseButtonEvent mouseButtonEvent, MouseEvent mouseEvent)
{
	int index = GetMouseButtonIndex(mouseButtonEvent.button);
	if (index == -1)
	{
		return;
	}
	mouseStates[index] = mouseEvent;
}

void Input::UpdateInput(SDL_Event* e, bool* quit)
{
	UpdateKeyboardStates();
	ResetMouseStates();

	while (SDL_PollEvent(e))
	{
		switch (e->type)
		{
		case SDL_QUIT:
			*quit = true;
			break;

		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			UpdateMouseState(e->button, DOWN);
			break;
		case SDL_MOUSEBUTTONUP:
			UpdateMouseState(e->button, UP);
			break;
		case SDL_MOUSEWHEEL:
			mouseScrollX = e->wheel.x;
			mouseScrollY = e->wheel.y;
			break;
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

bool Input::GetMouse(MouseButton button)
{
	return mouseStates[(int)button] == HELD;
}

bool Input::GetMouseDown(MouseButton button)
{
	return mouseStates[(int)button] == DOWN;
}

bool Input::GetMouseUp(MouseButton button)
{
	return mouseStates[(int)button] == UP;
}
