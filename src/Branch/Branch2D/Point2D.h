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
	class Point2D : public Branch2D
	{

		// # Variables + Getters/Setters
	private:

		Vector2 _PointPosition = Vector2();
		Color _Color = Color();

	public:

		PERCH_API inline Vector2 GetPointPosition() const { return _PointPosition; }
		PERCH_API inline void SetPointPosition(Vector2 position) { _PointPosition = position; }
		PERCH_API inline Color GetColor() const { return _Color; }
		PERCH_API inline void SetColor(Color color) { _Color = color; }

		// ###

		// # Functions

	private:
		
	public:

		PERCH_API Point2D(Engine* engine) : Branch2D(engine) {};

		PERCH_API Vector2 GetGlobalPointPosition();

		PERCH_API virtual void Draw(SDL_Renderer* renderer) override;

		// ###

	};


}
