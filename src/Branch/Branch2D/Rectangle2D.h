#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


#include "Branch2D.h"

#include "../../Structs/Rect2.h"
#include "../../Structs/Vector2.h"

#include <SDL.h>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	class Rectangle2D : public Branch2D
	{

		// # Variables + Getters/Setters
	private:

		Rect2 _Rect2 = Rect2();
		Color _Color = Color();

	public:

		PERCHENGINECPP_API inline Rect2 GetRect2() const { return _Rect2; }
		PERCHENGINECPP_API inline void SetRect2(Rect2 rect2) { _Rect2 = rect2; }
		PERCHENGINECPP_API inline Color GetColor() const { return _Color; }
		PERCHENGINECPP_API inline void SetColor(Color color) { _Color = color; }

		// ###

		// # Functions

	private:
		
	public:

		PERCHENGINECPP_API Rectangle2D(Engine* engine) : Branch2D(engine) {};

		PERCHENGINECPP_API Vector2 GetRectSize();
		PERCHENGINECPP_API Vector2 GetRectGlobalSize();

		PERCHENGINECPP_API Vector2 GetRectGlobalPosition();

		PERCHENGINECPP_API virtual void Draw(SDL_Renderer* renderer) override;

		// ###

	};


}
