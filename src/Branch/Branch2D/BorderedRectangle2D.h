#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


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

		float borderSize = 1.0f;
		Color borderColor = Color(0);

	public:

		PERCH_API inline float GetBorderSize() const { return borderSize; }
		PERCH_API inline void SetBorderSize(float size) { borderSize = size; }
		PERCH_API inline Color GetBorderColor() const { return borderColor; }
		PERCH_API inline void SetBorderColor(float color) { borderColor = color; }

		// ###


		// # Functions

	private:
		
	public:

		PERCH_API BorderedRectangle2D(Engine* engine) : Rectangle2D(engine) {};

		PERCH_API virtual void Draw(SDL_Renderer* renderer) override;

		// ###

	};


}
