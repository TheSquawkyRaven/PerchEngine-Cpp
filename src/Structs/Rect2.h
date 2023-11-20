#pragma once

#include <SDL.h>

#include "Vector2.h"
#include "Vector2i.h"

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	struct Rect2
	{

	private:
		SDL_Rect* SDLRect = new SDL_Rect;

	public:

	public:

		Rect2();
		Rect2(Vector2 position, Vector2 size);
		Rect2(float x, float y, float w, float h);

		Vector2 GetPosition();
		Vector2 GetSize();
		void SetPosition(Vector2 position);
		void SetPosition(Vector2i position);
		void SetPosition(float x, float y);
		void SetSize(Vector2 size);
		void SetSize(Vector2i size);
		void SetSize(float w, float h);

		SDL_Rect* GetSDLRect();

		static SDL_Rect* CreateSDLRect(Vector2* position, Vector2* size);

	};


}
