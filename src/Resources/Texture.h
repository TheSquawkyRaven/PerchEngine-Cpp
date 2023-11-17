#pragma once

#include "Resource.h"

#include <SDL.h>

#include "../Log.h"
#include "../Structs/Vector2i.h"

#include <memory>
#include <string>
#include "../Engine.h"

namespace Perch
{

	struct SDLTextureDeleter
	{
		void operator()(SDL_Texture* SDLTexture)
		{
			Squawk::Log::Print("Texture Destroyed");
			SDL_DestroyTexture(SDLTexture);
		}
	};

	/// <summary>
	/// 
	/// </summary>
	class Texture
	{

		// # Variables + Getters/Setters
	private:

		std::unique_ptr<SDL_Texture, SDLTextureDeleter> SDLTexture = NULL;
		Vector2i Size = Vector2i();

	public:
		inline SDL_Texture& GetSDLTexture() { return *SDLTexture; }

		Vector2i GetSize() const;

		// ###


		// # Functions

	private:
		Texture(SDL_Texture* sdlTexture);

	public:

		static std::shared_ptr<Texture> Create(Engine* engine, std::string path);

		// ###

	};


}
