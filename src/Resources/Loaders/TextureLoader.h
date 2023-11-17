#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	static class TextureLoader
	{

		// # Variables + Getters/Setters
		// ###


		// # Functions

	public:

		static SDL_Surface* LoadBMPSurface(SDL_Surface* mainWindowSurface, std::string path);

		static SDL_Surface* LoadSurface(SDL_Surface* mainWindowSurface, std::string path);

		// ###

	};


}
