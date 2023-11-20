#include "Point2D.h"

#include "../../Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

Vector2 Point2D::GetGlobalPointPosition()
{
	return _GetGlobalPosition() + _PointPosition;
}

void Point2D::Draw(Engine* engine, SDL_Renderer* renderer)
{
	Vector2 point = GetGlobalPointPosition();

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderDrawPoint(renderer, point.X, point.Y);
}
