#include "pch.h"

#include "Point2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void Point2D::Draw(SDL_Renderer* renderer)
{
	Vector2 point = GetGlobalPointPosition();

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(renderer, point.x, point.y);
}

Vector2 Point2D::GetGlobalPointPosition()
{
	return GetGlobalPosition() + pointPosition;
}
