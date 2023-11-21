#include "Vector2i.h"
#include "Viewport.h"

using namespace Perch;

Viewport::Viewport()
{}

Viewport::Viewport(Rect2 rect)
{
	Rect = rect;
}

SDL_Rect* Viewport::GetSDLRect()
{
	return Rect.GetSDLRect();
}
