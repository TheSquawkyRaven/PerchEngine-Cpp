#pragma once

#include "Rectangle2D.h"

#include "../../Structs/Rect2.h"
#include "../../Structs/Vector2.h"

#include <SDL.h>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	class BorderedRectangle2D : public Rectangle2D
	{

		// # Variables + Getters/Setters
	private:

		float BorderSize = 1.0f;
		// TODO + color

	public:

		inline float GetBorderSize() const { return BorderSize; }
		inline void SetBorderSize(float size) { BorderSize = size; }

		// ###


		// # Functions

	private:
		
	public:

		virtual void Draw(SDL_Renderer* renderer) override;

		// ###

	};


}
