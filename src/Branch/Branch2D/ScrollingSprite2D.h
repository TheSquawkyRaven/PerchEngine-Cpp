#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


#include "Sprite2D.h"

#include <SDL.h>

#include <memory>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	class ScrollingSprite2D : public Sprite2D
	{

		// # Variables + Getters/Setters
	public:

		bool isHorizontal = true;
		int tileTexture = 1;
		// Scroll is what moves the textures. Not to be confused with position as position is the anchor
		float scroll = 0.0f;

		// ###


		// # Functions

	private:

		
	protected:


	public:

		PERCH_API ScrollingSprite2D(Engine* engine) : Sprite2D(engine) {};
		
		virtual void Draw(Renderer* renderer) override;

		// ###

	};


}
