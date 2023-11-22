#pragma once

#include <SDL.h>

#include "Rect2.h"

#include <memory>

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
		std::shared_ptr<SDL_Rect> GetSDLRect();

	};


}
