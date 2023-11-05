#pragma once

#include <SDL.h>

#include "Vector2.h"

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	struct Rect2D
	{

	private:
		SDL_Rect* Rect2D;

	public:
		
		Vector2 Position;
		Vector2 Scale;

	public:
		SDL_Rect* GetSDLRect();

		static SDL_Rect* CreateSDLRect(Vector2* position, Vector2* size);

	};


}
