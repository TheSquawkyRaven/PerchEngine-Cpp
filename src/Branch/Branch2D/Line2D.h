#pragma once

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

		inline Vector2 GetStartPosition() const { return _StartPosition; }
		inline Vector2 GetEndPosition() const { return _EndPosition; }
		inline void SetStartPosition(Vector2 position) { _StartPosition = position; }
		inline void SetEndPosition(Vector2 position) { _EndPosition = position; }
		inline Color GetColor() const { return _Color; }
		inline void SetColor(Color color) { _Color = color; }

		// ###

		// # Functions

	private:

	public:

		Vector2 GetGlobalStartPosition();
		Vector2 GetGlobalEndPosition();

		virtual void Draw(Engine* engine, SDL_Renderer* renderer) override;

		// ###

	};

}
