#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
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

		PERCHENGINECPP_API inline Vector2 GetStartPosition() const { return _StartPosition; }
		PERCHENGINECPP_API inline Vector2 GetEndPosition() const { return _EndPosition; }
		PERCHENGINECPP_API inline void SetStartPosition(Vector2 position) { _StartPosition = position; }
		PERCHENGINECPP_API inline void SetEndPosition(Vector2 position) { _EndPosition = position; }
		PERCHENGINECPP_API inline Color GetColor() const { return _Color; }
		PERCHENGINECPP_API inline void SetColor(Color color) { _Color = color; }

		// ###

		// # Functions

	private:

	public:

		PERCHENGINECPP_API Line2D(Engine* engine) : Branch2D(engine) {};

		PERCHENGINECPP_API Vector2 GetGlobalStartPosition();
		PERCHENGINECPP_API Vector2 GetGlobalEndPosition();

		PERCHENGINECPP_API virtual void Draw(SDL_Renderer* renderer) override;

		// ###

	};

}
