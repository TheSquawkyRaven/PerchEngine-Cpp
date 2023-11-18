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
		// TODO + color

	public:

		inline Vector2 GetStartPosition() const { return _StartPosition; }
		inline Vector2 GetEndPosition() const { return _EndPosition; }
		inline void SetStartPosition(Vector2 position) { _StartPosition = position; }
		inline void SetEndPosition(Vector2 position) { _EndPosition = position; }

		// ###

		// # Functions

	private:

	public:

		Vector2 GetGlobalStartPosition();
		Vector2 GetGlobalEndPosition();

		virtual void Draw(SDL_Renderer* renderer) override;

		// ###

	};

}
