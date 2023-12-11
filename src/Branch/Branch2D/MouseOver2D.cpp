#include "pch.h"

#include "../../Squawk/Log.h"
#include "MouseOver2D.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

void MouseOver2D::UpdateRect()
{
	Vector2 pos = GetGlobalPosition();
	globalRect.SetPosition(pos);
	Vector2 scale = GetGlobalScale();
	globalRect.SetSize(rect.GetSize() * scale);
}

void MouseOver2D::Update()
{
	Vector2 mousePosition = engine->GetInput()->GetMousePosition();
	// TODO change to using pivot, global scale, etc. Refer sprite draw function
	UpdateRect();
	bool mouseInRect = globalRect.PointIsIn(mousePosition);
	if (!mouseWasInRect && mouseInRect)
	{
		mouseWasInRect = true;
		OnMouseOver(MouseOverState::Hover);
	}
	else if (mouseWasInRect && !mouseInRect)
	{
		mouseWasInRect = false;
		OnMouseOver(MouseOverState::Exit);
	}
	if (mouseInRect)
	{
		if (engine->GetInput()->GetMouseDown(Input::LEFT))
		{
			clickStartedInRect = true;
			OnMouseOver(MouseOverState::Down);
		}
	}
	if (clickStartedInRect)
	{
		if (engine->GetInput()->GetMouseUp(Input::LEFT))
		{
			clickStartedInRect = false;
			OnMouseOver(MouseOverState::Up);

			if (mouseInRect)
			{
				OnMouseOver(MouseOverState::Click);
			}
		}
	}
}

void MouseOver2D::OnMouseOver(MouseOverState state)
{}
