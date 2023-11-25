#include "pch.h"

#include "Vector2i.h"
#include "Viewport.h"

using namespace Perch;
using namespace std;

Viewport::Viewport()
{}

Viewport::Viewport(Rect2 rect)
{
	Rect = rect;
}

shared_ptr<SDL_Rect> Viewport::GetSDLRect()
{
	return Rect.GetSDLRect();
}
