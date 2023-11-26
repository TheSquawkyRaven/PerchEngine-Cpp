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
	class Point2D : public Branch2D
	{

		// # Variables + Getters/Setters
	private:

		Vector2 _PointPosition = Vector2();
		Color _Color = Color();

	public:

		PERCHENGINECPP_API inline Vector2 GetPointPosition() const { return _PointPosition; }
		PERCHENGINECPP_API inline void SetPointPosition(Vector2 position) { _PointPosition = position; }
		PERCHENGINECPP_API inline Color GetColor() const { return _Color; }
		PERCHENGINECPP_API inline void SetColor(Color color) { _Color = color; }

		// ###

		// # Functions

	private:
		
	public:

		PERCHENGINECPP_API Point2D(Engine* engine) : Branch2D(engine) {};

		PERCHENGINECPP_API Vector2 GetGlobalPointPosition();

		PERCHENGINECPP_API virtual void Draw(SDL_Renderer* renderer) override;

		// ###

	};


}
