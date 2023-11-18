#include "Rect2.h"

using namespace Perch;

Rect2::Rect2()
{
}

Rect2::Rect2(Vector2 position, Vector2 size)
{
	Position = position;
	Size = size;
}

Rect2::Rect2(float x, float y, float w, float h)
{
	Position = Vector2(x, y);
	Size = Vector2(w, h);
}

SDL_Rect* Rect2::GetSDLRect()
{
	SDLRect->x = Position.X;
	SDLRect->y = Position.Y;
	SDLRect->w = Size.X;
	SDLRect->h = Size.Y;

	return SDLRect;
}

SDL_Rect* Rect2::CreateSDLRect(Vector2* position, Vector2* size)
{
	SDL_Rect* rect = new SDL_Rect{};
	rect->x = position->X;
	rect->y = position->Y;
	rect->w = size->X;
	rect->h = size->Y;

	return rect;
}
