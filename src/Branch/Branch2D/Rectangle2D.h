#pragma once

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
		// TODO + color

	public:

		inline Rect2 GetRect2() const { return _Rect2; }
		inline void SetRect2(Rect2 rect2) { _Rect2 = rect2; }

		// ###

		// # Functions

	private:
		
	public:

		Vector2 GetRectSize();
		Vector2 GetRectGlobalSize();

		Vector2 GetRectGlobalPosition();

		virtual void Draw(Engine* engine, SDL_Renderer* renderer) override;

		// ###

	};


}
