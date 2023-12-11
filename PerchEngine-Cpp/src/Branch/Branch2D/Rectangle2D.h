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

		Rect2 globalRect = Rect2();

	public:

		Rect2 rect = Rect2();
		Color color = Color();

		// ###

		// # Functions

	private:
		
	public:

		PERCH_API Rectangle2D(Engine* engine) : Branch2D(engine) {};

		PERCH_API virtual void SetupDraw(Renderer* renderer) override;
		PERCH_API virtual void Draw(Renderer* renderer) override;

		PERCH_API Vector2 GetRectSize();
		PERCH_API Vector2 GetRectGlobalSize();

		PERCH_API Vector2 GetRectGlobalPosition();

		// ###

	};


}
