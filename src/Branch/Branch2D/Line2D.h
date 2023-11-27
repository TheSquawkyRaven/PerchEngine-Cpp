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

		Vector2 _StartPosition = Vector2();
		Vector2 _EndPosition = Vector2();
		Color _Color = Color();

	public:

		PERCH_API inline Vector2 GetStartPosition() const { return _StartPosition; }
		PERCH_API inline Vector2 GetEndPosition() const { return _EndPosition; }
		PERCH_API inline void SetStartPosition(Vector2 position) { _StartPosition = position; }
		PERCH_API inline void SetEndPosition(Vector2 position) { _EndPosition = position; }
		PERCH_API inline Color GetColor() const { return _Color; }
		PERCH_API inline void SetColor(Color color) { _Color = color; }

		// ###

		// # Functions

	private:

	public:

		PERCH_API Line2D(Engine* engine) : Branch2D(engine) {};

		PERCH_API Vector2 GetGlobalStartPosition();
		PERCH_API Vector2 GetGlobalEndPosition();

		PERCH_API virtual void Draw(SDL_Renderer* renderer) override;

		// ###

	};

}
