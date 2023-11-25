#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


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

		PERCHENGINECPP_API Viewport();
		PERCHENGINECPP_API Viewport(Rect2 rect);
		PERCHENGINECPP_API std::shared_ptr<SDL_Rect> GetSDLRect();

	};


}
