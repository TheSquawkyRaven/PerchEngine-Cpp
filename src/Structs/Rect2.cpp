#include "pch.h"

#include "Rect2.h"

using namespace Perch;
using namespace std;

void Rect2::UpdateSDLRect()
{
	SDLRect->x = (int)(Position.X + 0.5f);
	SDLRect->y = (int)(Position.Y + 0.5f);
	SDLRect->w = (int)(Size.X + 0.5f);
	SDLRect->h = (int)(Size.Y + 0.5f);
}

Rect2::Rect2()
{
	UpdateSDLRect();
}

Rect2::Rect2(Vector2 position, Vector2 size)
{
	SetPosition(position);
	SetSize(size);
}

Rect2::Rect2(float x, float y, float w, float h)
{
	SetPosition(x, y);
	SetSize(w, h);
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
	Position = Vector2(x, y);
	UpdateSDLRect();
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
	Size = Vector2(w, h);
	UpdateSDLRect();
}

shared_ptr<SDL_Rect> Rect2::GetSDLRect()
{
	return SDLRect;
}

shared_ptr<SDL_Rect> Rect2::CreateSDLRect(Vector2 position, Vector2 size)
{
	shared_ptr<SDL_Rect> rect = shared_ptr<SDL_Rect>(new SDL_Rect);
	rect->x = position.X;
	rect->y = position.Y;
	rect->w = size.X;
	rect->h = size.Y;

	return rect;
}
