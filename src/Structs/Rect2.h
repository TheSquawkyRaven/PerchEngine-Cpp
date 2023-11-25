#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


#include <SDL.h>

#include "Vector2.h"
#include "Vector2i.h"

#include <memory>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	struct Rect2
	{

	private:

		Vector2 Position = Vector2();
		Vector2 Size = Vector2();
		// SDLRect is cached here because it is almost always used
		std::shared_ptr<SDL_Rect> SDLRect = std::shared_ptr<SDL_Rect>(new SDL_Rect);

	public:

	private:

		void UpdateSDLRect();

	public:

		PERCHENGINECPP_API Rect2();
		PERCHENGINECPP_API Rect2(Vector2 position, Vector2 size);
		PERCHENGINECPP_API Rect2(float x, float y, float w, float h);

		PERCHENGINECPP_API Vector2 GetPosition();
		PERCHENGINECPP_API Vector2 GetSize();
		PERCHENGINECPP_API void SetPosition(Vector2 position);
		PERCHENGINECPP_API void SetPosition(Vector2i position);
		PERCHENGINECPP_API void SetPosition(float x, float y);
		PERCHENGINECPP_API void SetSize(Vector2 size);
		PERCHENGINECPP_API void SetSize(Vector2i size);
		PERCHENGINECPP_API void SetSize(float w, float h);

		PERCHENGINECPP_API std::shared_ptr<SDL_Rect> GetSDLRect();

		PERCHENGINECPP_API static std::shared_ptr<SDL_Rect> CreateSDLRect(Vector2 position, Vector2 size);

	};


}
