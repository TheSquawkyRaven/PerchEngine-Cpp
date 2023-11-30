#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


// Main SDL Window
#include <SDL.h>

#include "../Structs/Color.h"
#include "../Structs/Rect2.h"
#include "../Structs/Texture.h"
#include "../Structs/Vector2.h"
#include "../Structs/Vector2i.h"
#include "../Structs/Viewport.h"

#include <memory>


namespace Perch
{

	class Renderer
	{

		// # Variables + Getters/Setters

	private:


	public:

		// ###


		// # Functions

	private:

	public:

		virtual void Draw() = 0;


		// ###
	};
}
