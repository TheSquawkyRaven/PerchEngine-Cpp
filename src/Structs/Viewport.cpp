#include "Vector2i.h"
#include "Viewport.h"

using namespace Perch;

Viewport::Viewport(Rect2* rect)
{
	_Rect = rect;
}

SDL_Rect* Viewport::GetSDLRect()
{
	return _Rect->GetSDLRect();
}
