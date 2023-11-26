#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
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

		float _BorderSize = 1.0f;
		Color _BorderColor = Color(0);

	public:

		PERCHENGINECPP_API inline float GetBorderSize() const { return _BorderSize; }
		PERCHENGINECPP_API inline void SetBorderSize(float size) { _BorderSize = size; }
		PERCHENGINECPP_API inline Color GetBorderColor() const { return _BorderColor; }
		PERCHENGINECPP_API inline void SetBorderColor(float color) { _BorderColor = color; }

		// ###


		// # Functions

	private:
		
	public:

		PERCHENGINECPP_API BorderedRectangle2D(Engine* engine) : Rectangle2D(engine) {};

		PERCHENGINECPP_API virtual void Draw(SDL_Renderer* renderer) override;

		// ###

	};


}
