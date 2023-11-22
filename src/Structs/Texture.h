#pragma once

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
	struct Texture
	{

		// # Variables + Getters/Setters
	private:

		std::unique_ptr<SDL_Texture, SDLTextureDeleter> SDLTexture = NULL;
		Vector2i Size = Vector2i();

	public:
		inline SDL_Texture* GetSDLTexture() { return SDLTexture.get(); }

		Vector2i GetSize() const;

		// ###


		// # Functions

	private:

		static SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path);

		Texture(SDL_Texture* sdlTexture);

	public:

		static std::shared_ptr<Texture> Create(Engine* engine, std::string path);

		// ###

	};


}
