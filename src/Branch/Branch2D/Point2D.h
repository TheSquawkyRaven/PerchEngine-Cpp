#pragma once

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

		inline Vector2 GetPointPosition() const { return _PointPosition; }
		inline void SetPointPosition(Vector2 position) { _PointPosition = position; }
		inline Color GetColor() const { return _Color; }
		inline void SetColor(Color color) { _Color = color; }

		// ###

		// # Functions

	private:
		
	public:

		Vector2 GetGlobalPointPosition();

		virtual void Draw(Engine* engine, SDL_Renderer* renderer) override;

		// ###

	};


}
