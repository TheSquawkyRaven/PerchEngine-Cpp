#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
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

		PERCH_API inline Rect2 GetRect2() const { return _Rect2; }
		PERCH_API inline void SetRect2(Rect2 rect2) { _Rect2 = rect2; }
		PERCH_API inline Color GetColor() const { return _Color; }
		PERCH_API inline void SetColor(Color color) { _Color = color; }

		// ###

		// # Functions

	private:
		
	public:

		PERCH_API Rectangle2D(Engine* engine) : Branch2D(engine) {};

		PERCH_API Vector2 GetRectSize();
		PERCH_API Vector2 GetRectGlobalSize();

		PERCH_API Vector2 GetRectGlobalPosition();

		PERCH_API virtual void Draw(SDL_Renderer* renderer) override;

		// ###

	};


}
