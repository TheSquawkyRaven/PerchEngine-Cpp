#include "pch.h"

#include "../../Squawk/Log.h"
#include "MouseOver2D.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

void MouseOver2D::Update()
{
	Vector2 mousePosition = engine->GetInput()->GetMousePosition();
	// TODO change to using pivot, global scale, etc. Refer sprite draw function
	bool mouseInRect = rect.PointIsIn(mousePosition);
	if (!mouseWasInRect && mouseInRect)
	{
		mouseWasInRect = true;
		OnMouseHover();
	}
	else if (mouseWasInRect && !mouseInRect)
	{
		mouseWasInRect = false;
		OnMouseExit();
	}
	if (mouseInRect)
	{
		if (engine->GetInput()->GetMouseDown(Input::LEFT))
		{
			clickStartedInRect = true;
			OnMouseDown();
		}
	}
	if (clickStartedInRect)
	{
		if (engine->GetInput()->GetMouseUp(Input::LEFT))
		{
			clickStartedInRect = false;
			OnMouseUp();

			if (mouseInRect)
			{
				OnMouseClick();
			}
		}
	}
}

void MouseOver2D::OnMouseHover()
{}

void MouseOver2D::OnMouseExit()
{}

void MouseOver2D::OnMouseDown()
{}

void MouseOver2D::OnMouseUp()
{}

void MouseOver2D::OnMouseClick()
{}
