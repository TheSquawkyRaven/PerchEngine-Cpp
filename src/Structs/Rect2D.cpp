#include "Rect2D.h"

using namespace Perch;

SDL_Rect* Rect2D::GetSDLRect()
{
	Rect2D->x = Position.X;
	Rect2D->y = Position.Y;
	Rect2D->w = Scale.X;
	Rect2D->h = Scale.Y;

	return Rect2D;
}

SDL_Rect* Perch::Rect2D::CreateSDLRect(Vector2* position, Vector2* size)
{
	SDL_Rect* rect = new SDL_Rect{};
	rect->x = position->X;
	rect->y = position->Y;
	rect->w = size->X;
	rect->h = size->Y;

	return rect;
}
