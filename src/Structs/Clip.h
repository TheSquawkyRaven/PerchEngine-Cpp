#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


#include <SDL.h>
#include <SDL_mixer.h>

#include "../Squawk/Log.h"
#include "../Structs/Vector2i.h"

#include <memory>
#include <string>
#include "../Engine.h"

namespace Perch
{

	struct SDLClipDeleter
	{
		void operator()(Mix_Chunk* sdlMixChunk)
		{
			Squawk::Log::Print("Mix Chunk Destroyed");
			Mix_FreeChunk(sdlMixChunk);
		}
	};

	/// <summary>
	/// 
	/// </summary>
	struct Clip
	{

		// # Variables + Getters/Setters
	private:

		std::unique_ptr<Mix_Chunk, SDLClipDeleter> sdlMixChunk = nullptr;

	public:

		PERCH_API inline Mix_Chunk* GetSDLMixChunk() { return sdlMixChunk.get(); }

		// ###


		// # Functions

	private:

		static Mix_Chunk* LoadMixChunk(std::string path);

		Clip(Mix_Chunk* sdlMixChunk);

	public:

		PERCH_API static std::shared_ptr<Clip> Create(Engine* engine, std::string path);

		// ###

	};


}
