#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


#include "Branch2D.h"

#include <SDL.h>

namespace Perch
{

	enum class MouseOverState
	{
		// Mouse position in rect
		Hover,
		// Mouse position left rect (when stopped hovering)
		Exit,
		// Click starts in rect
		Down,
		// Click released (may or may not still be in rect, runs if click started in rect)
		Up,
		// Click started and released in rect (both started and released in rect)
		Click,
	};

	/// <summary>
	/// 
	/// </summary>
	class MouseOver2D : public Branch2D
	{

		// # Variables + Getters/Setters

	private:

		Rect2 globalRect = Rect2();

		bool mouseWasInRect = false;
		bool clickStartedInRect = false;

	public:
		// Note that if this is used as a child of Sprite2D, the pivot will be ignored! TODO Change in the future?
		Rect2 rect = Rect2();

		// ###


		// # Functions
		// ###

	private:

		void UpdateRect();

	public:

		PERCH_API MouseOver2D(Engine* engine) : Branch2D(engine) {};

		PERCH_API virtual void Update() override;
		PERCH_API virtual void OnMouseOver(MouseOverState state);


	};


}
