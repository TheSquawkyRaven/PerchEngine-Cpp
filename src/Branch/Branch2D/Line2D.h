#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


#include "Branch2D.h"

#include "../../Structs/Vector2.h"

#include <SDL.h>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	class Line2D : public Branch2D
	{

		// # Variables + Getters/Setters

	public:

		Vector2 startPosition = Vector2();
		Vector2 endPosition = Vector2();

		Color color = Color();

		// ###

		// # Functions

	private:

	public:

		PERCH_API Line2D(Engine* engine) : Branch2D(engine) {};

		PERCH_API virtual void Draw(Renderer* renderer) override;

		PERCH_API Vector2 GetGlobalStartPosition();
		PERCH_API Vector2 GetGlobalEndPosition();

		// ###

	};

}
