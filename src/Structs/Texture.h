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

namespace Perch
{

	class Engine;

	class Renderer;
	class SDLRenderer;

	/// <summary>
	/// 
	/// </summary>
	struct Texture
	{

		friend Renderer;
		friend SDLRenderer;

	private:

		struct SDLTextureDeleter
		{
			void operator()(SDL_Texture* sdlTexture)
			{
				Squawk::Log::Print("Texture Destroyed");
				SDL_DestroyTexture(sdlTexture);
			}
		};

		// # Variables + Getters/Setters
	private:

		std::unique_ptr<SDL_Texture, SDLTextureDeleter> sdlTexture = nullptr;
		Vector2i size = Vector2i();

	public:

		PERCH_API Vector2i GetSize() const;

		// ###


		// # Functions

	private:
		
		Texture(SDL_Texture* sdlTexture);

	public:

		PERCH_API static std::shared_ptr<Texture> Create(Engine* engine, std::string path);
		PERCH_API static std::shared_ptr<Texture> Create(Engine* engine, std::shared_ptr<Font> font, std::string text, int fontSize, Color color);

		// ###

	};


}
