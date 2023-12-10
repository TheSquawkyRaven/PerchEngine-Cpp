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

	/// <summary>
	/// 
	/// </summary>
	class MouseOver2D : public Branch2D
	{

		// # Variables + Getters/Setters

	private:

		bool mouseWasInRect = false;
		bool clickStartedInRect = false;

	public:
		// Note that if this is used as a child of Sprite2D, the pivot will be ignored! TODO Change in the future?
		Rect2 rect = Rect2();

		// ###


		// # Functions
		// ###

	public:

		PERCH_API MouseOver2D(Engine* engine) : Branch2D(engine) {};

		PERCH_API virtual void Update() override;
		// Mouse position in rect
		PERCH_API virtual void OnMouseHover();
		// Mouse position left rect (when stopped hovering)
		PERCH_API virtual void OnMouseExit();
		// Click starts in rect
		PERCH_API virtual void OnMouseDown();
		// Click released (may or may not still be in rect, runs if click started in rect)
		PERCH_API virtual void OnMouseUp();
		// Click started and released in rect (both started and released in rect)
		PERCH_API virtual void OnMouseClick();


	};


}
