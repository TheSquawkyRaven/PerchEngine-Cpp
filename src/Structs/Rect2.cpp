#include "Rect2.h"

using namespace Perch;

Rect2::Rect2()
{
	SDLRect->x = 0;
	SDLRect->y = 0;
	SDLRect->w = 0;
	SDLRect->h = 0;
}

Rect2::Rect2(Vector2 position, Vector2 size)
{
	SDLRect->x = position.X;
	SDLRect->y = position.Y;
	SDLRect->w = size.X;
	SDLRect->h = size.Y;
}

Rect2::Rect2(float x, float y, float w, float h)
{
	SDLRect->x = x;
	SDLRect->y = y;
	SDLRect->w = w;
	SDLRect->h = h;
}

Vector2 Rect2::GetPosition()
{
	return Vector2(SDLRect->x, SDLRect->y);
}

Vector2 Rect2::GetSize()
{
	return Vector2(SDLRect->w, SDLRect->h);
}

void Rect2::SetPosition(Vector2 position)
{
	SetPosition(position.X, position.Y);
}

void Rect2::SetPosition(Vector2i position)
{
	SetPosition(position.X, position.Y);
}

void Rect2::SetPosition(float x, float y)
{
	SDLRect->x = x;
	SDLRect->y = y;
}

void Rect2::SetSize(Vector2 size)
{
	SetSize(size.X, size.Y);
}

void Rect2::SetSize(Vector2i size)
{
	SetSize(size.X, size.Y);
}

void Rect2::SetSize(float w, float h)
{
	SDLRect->w = w;
	SDLRect->h = h;
}

SDL_Rect* Rect2::GetSDLRect()
{
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
