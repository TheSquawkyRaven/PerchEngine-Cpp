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

		float _BorderSize = 1.0f;
		Color _BorderColor = Color(0);

	public:

		inline float GetBorderSize() const { return _BorderSize; }
		inline void SetBorderSize(float size) { _BorderSize = size; }
		inline Color GetBorderColor() const { return _BorderColor; }
		inline void SetBorderColor(float color) { _BorderColor = color; }

		// ###


		// # Functions

	private:
		
	public:

		virtual void Draw(SDL_Renderer* renderer) override;

		// ###

	};


}
