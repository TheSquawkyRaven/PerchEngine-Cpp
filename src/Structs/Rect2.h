#pragma once

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
		std::shared_ptr<SDL_Rect> SDLRect = std::shared_ptr<SDL_Rect>(new SDL_Rect);

	public:

	private:

		void UpdateSDLRect();

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

		std::shared_ptr<SDL_Rect> GetSDLRect();

		static std::shared_ptr<SDL_Rect> CreateSDLRect(Vector2 position, Vector2 size);

	};


}
