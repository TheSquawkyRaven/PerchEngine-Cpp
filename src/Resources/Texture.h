#pragma once

#include "Resource.h"

#include <SDL.h>

#include "../Structs/Vector2.h"

#include <memory>
#include <string>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	class Texture
	{

	public:
		enum TextureFileFormat
		{
			FORMAT_BMP,
			FORMAT_PNG
		};

		// # Variables + Getters/Setters
	private:

		std::unique_ptr<SDL_Surface> SDLSurface = NULL;

	public:
		inline SDL_Surface& GetSDLSurface() { return *SDLSurface; }

		Vector2 GetSize() const;

		// ###


		// # Functions

	private:
		Texture(SDL_Surface* surface);

	public:

		static Texture* Create(SDL_Surface* mainWindowSurface, std::string path, TextureFileFormat fileFormat);

		// ###

	};


}
