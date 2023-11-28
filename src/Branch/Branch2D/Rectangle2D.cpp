#include "pch.h"

#include "Rectangle2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void Rectangle2D::Draw(SDL_Renderer* renderer)
{
	Vector2 position = GetRectGlobalPosition();
	Vector2 size = GetRectSize();

	shared_ptr<SDL_Rect> rect = Rect2::CreateSDLRect(position, size);

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, rect.get());
}

Vector2 Rectangle2D::GetRectSize()
{
	Vector2 size = rect.GetSize();
	return Vector2(scale.x * size.x, scale.y * size.y);
}

Vector2 Rectangle2D::GetRectGlobalSize()
{
	Vector2 size = rect.GetSize();
	Vector2 scale = GetGlobalScale();
	return Vector2(scale.x * size.x, scale.y * size.y);
}

Vector2 Rectangle2D::GetRectGlobalPosition()
{
	return GetGlobalPosition() + rect.GetPosition();
}
