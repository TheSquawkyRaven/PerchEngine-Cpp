#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


#include <SDL.h>
#include <SDL_ttf.h>

#include "../Log.h"
#include "../Structs/Vector2i.h"

#include <memory>
#include <string>
#include "../Engine.h"

namespace Perch
{

	struct SDLFontDeleter
	{
		void operator()(TTF_Font* sdlFont)
		{
			Squawk::Log::Print("Font Destroyed");
			TTF_CloseFont(sdlFont);
		}
	};

	/// <summary>
	/// 
	/// </summary>
	struct Font
	{

		// # Variables + Getters/Setters
	private:

		std::unique_ptr<TTF_Font, SDLFontDeleter> SDLFont = NULL;

	public:

		PERCHENGINECPP_API inline TTF_Font* GetSDLFont() { return SDLFont.get(); }

		// ###


		// # Functions

	private:

		static TTF_Font* LoadTTF(std::string path, int fontSize);

		Font(TTF_Font* sdlFont);

	public:

		PERCHENGINECPP_API static std::shared_ptr<Font> Create(Engine* engine, std::string path, int fontSize);

		// ###

	};


}
