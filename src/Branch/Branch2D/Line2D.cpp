#include "pch.h"

#include "Line2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void Line2D::Draw(SDL_Renderer* renderer)
{
	Vector2 start = GetGlobalStartPosition();
	Vector2 end = GetGlobalEndPosition();

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
}

Vector2 Line2D::GetGlobalStartPosition()
{
	return GetGlobalPosition() + startPosition;
}

Vector2 Line2D::GetGlobalEndPosition()
{
	return GetGlobalPosition() + endPosition;
}
