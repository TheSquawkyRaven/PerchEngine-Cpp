#pragma once

#include <SDL.h>

#include "../Log.h"
#include "../Structs/Vector2i.h"
#include "../Structs/Color.h"
#include "../Structs/Font.h"

#include <memory>
#include <string>
#include "../Engine.h"

namespace Perch
{

	struct SDLTextureDeleter
	{
		void operator()(SDL_Texture* sdlTexture)
		{
			Squawk::Log::Print("Texture Destroyed");
			SDL_DestroyTexture(sdlTexture);
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
		static std::shared_ptr<Texture> Create(Engine* engine, std::shared_ptr<Font> font, std::string text, Color color);

		// ###

	};


}
