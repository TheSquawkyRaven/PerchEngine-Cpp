#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


// Main SDL Window
#include <SDL.h>

#include "Renderer.h"

#include <memory>


namespace Perch
{

	class SDLRenderer : public Renderer
	{

		// # Variables + Getters/Setters

	private:


	public:

		// ###


		// # Functions

	private:

	public:



		// ###
	};
}
