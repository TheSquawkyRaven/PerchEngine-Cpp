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

		static SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path);

		// ###

	};


}
