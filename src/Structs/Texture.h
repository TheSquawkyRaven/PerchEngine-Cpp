#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


#include <SDL.h>

#include "../Squawk/Log.h"
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

		std::unique_ptr<SDL_Texture, SDLTextureDeleter> sdlTexture = nullptr;
		Vector2i size = Vector2i();

	public:
		PERCH_API inline SDL_Texture* GetSDLTexture() { return sdlTexture.get(); }

		PERCH_API Vector2i GetSize() const;

		// ###


		// # Functions

	private:

		static SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path);

		Texture(SDL_Texture* sdlTexture);

	public:

		PERCH_API static std::shared_ptr<Texture> Create(Engine* engine, std::string path);
		PERCH_API static std::shared_ptr<Texture> Create(Engine* engine, std::shared_ptr<Font> font, std::string text, Color color);

		// ###

	};


}
