#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


#include <SDL.h>
#include <SDL_ttf.h>

#include "../Squawk/Log.h"
#include "../Structs/Vector2i.h"

#include <memory>
#include <string>

namespace Perch
{

	class Engine;

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

		std::unique_ptr<TTF_Font, SDLFontDeleter> sdlFont = nullptr;

	public:

		PERCH_API inline TTF_Font* GetSDLFont() { return sdlFont.get(); }

		// ###


		// # Functions

	private:

		static TTF_Font* LoadTTF(std::string path);

		Font(TTF_Font* sdlFont);

	public:

		PERCH_API static std::shared_ptr<Font> Create(Engine* engine, std::string path);

		void SetFontSize(int fontSize);

		// ###

	};


}
