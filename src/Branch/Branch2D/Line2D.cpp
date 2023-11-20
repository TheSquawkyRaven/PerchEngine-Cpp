#include "Line2D.h"

#include "../../Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

Vector2 Line2D::GetGlobalStartPosition()
{
	return _GetGlobalPosition() + _StartPosition;
}

Vector2 Line2D::GetGlobalEndPosition()
{
	return _GetGlobalPosition() + _EndPosition;
}

void Line2D::Draw(Engine* engine, SDL_Renderer* renderer)
{
	Vector2 start = GetGlobalStartPosition();
	Vector2 end = GetGlobalEndPosition();

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
	SDL_RenderDrawLine(renderer, start.X, start.Y, end.X, end.Y);
}
