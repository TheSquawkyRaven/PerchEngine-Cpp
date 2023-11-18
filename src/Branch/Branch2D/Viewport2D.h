#pragma once

#include "Branch2D.h"

#include "../../Structs/Vector2.h"
#include "../../Structs/Rect2.h"

#include <SDL.h>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	// Children are drawn on this viewport
	class Viewport2D : public Branch2D
	{

		// # Variables + Getters/Setters
	private:
		Rect2 _ViewportRect = Rect2(0, 0, 100, 100);

	public:

		// ###

		// # Functions

	private:

	public:

		virtual void Draw(SDL_Renderer* renderer) override;

		// ###

	};


}
