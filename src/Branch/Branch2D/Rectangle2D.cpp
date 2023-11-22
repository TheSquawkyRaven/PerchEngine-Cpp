#include "Rectangle2D.h"

#include "../../Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

Vector2 Rectangle2D::GetRectSize()
{
	Vector2 size = _Rect2.GetSize();
	return Vector2(Scale.X * size.X, Scale.Y * size.Y);
}

Vector2 Rectangle2D::GetRectGlobalSize()
{
	Vector2 size = _Rect2.GetSize();
	Vector2 scale = GetGlobalScale();
	return Vector2(scale.X * size.X, scale.Y * size.Y);
}

Vector2 Rectangle2D::GetRectGlobalPosition()
{
	return _GetGlobalPosition() + _Rect2.GetPosition();
}

void Rectangle2D::Draw(SDL_Renderer* renderer)
{
	Vector2 position = GetRectGlobalPosition();
	Vector2 size = GetRectSize();

	shared_ptr<SDL_Rect> rect = Rect2::CreateSDLRect(position, size);

	SDL_SetRenderDrawColor(renderer, _Color.R, _Color.G, _Color.B, _Color.A);
	SDL_RenderFillRect(renderer, rect.get());
}
