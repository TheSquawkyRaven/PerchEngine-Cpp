#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
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

		PERCH_API Viewport();
		PERCH_API Viewport(Rect2 rect);
		PERCH_API std::shared_ptr<SDL_Rect> GetSDLRect();

	};


}
