#pragma once

#include <SDL.h>

#include "Vector2.h"

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	struct Rect2
	{

	private:
		SDL_Rect* SDLRect = new SDL_Rect;

	public:
		
		Vector2 Position = Vector2();
		Vector2 Size = Vector2();

	public:

		Rect2();
		Rect2(Vector2 position, Vector2 size);
		Rect2(float x, float y, float w, float h);

		SDL_Rect* GetSDLRect();

		static SDL_Rect* CreateSDLRect(Vector2* position, Vector2* size);

	};


}
