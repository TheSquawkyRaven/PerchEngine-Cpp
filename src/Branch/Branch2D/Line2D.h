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
	private:

		Vector2 startPosition = Vector2();
		Vector2 endPosition = Vector2();
		Color color = Color();

	public:

		PERCH_API inline Vector2 GetStartPosition() const { return startPosition; }
		PERCH_API inline Vector2 GetEndPosition() const { return endPosition; }
		PERCH_API inline void SetStartPosition(Vector2 position) { startPosition = position; }
		PERCH_API inline void SetEndPosition(Vector2 position) { endPosition = position; }
		PERCH_API inline Color GetColor() const { return color; }
		PERCH_API inline void SetColor(Color color) { this->color = color; }

		// ###

		// # Functions

	private:

	public:

		PERCH_API Line2D(Engine* engine) : Branch2D(engine) {};

		PERCH_API virtual void Draw(SDL_Renderer* renderer) override;

		PERCH_API Vector2 GetGlobalStartPosition();
		PERCH_API Vector2 GetGlobalEndPosition();

		// ###

	};

}
