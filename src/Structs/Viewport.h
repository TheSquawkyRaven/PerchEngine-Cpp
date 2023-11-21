#pragma once

#include <SDL.h>

#include "Rect2.h"

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	struct Viewport
	{

	public:

		Rect2 Rect = Rect2();


	public:

		Viewport();
		Viewport(Rect2 rect);
		SDL_Rect* GetSDLRect();

	};


}
