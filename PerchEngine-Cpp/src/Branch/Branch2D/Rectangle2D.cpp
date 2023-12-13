

#include "Rectangle2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void Rectangle2D::SetupDraw(Renderer* renderer)
{
	SetupDefaultDrawOrder(renderer);
}

void Rectangle2D::Draw(Renderer* renderer)
{
	Vector2 position = GetRectGlobalPosition();
	Vector2 size = GetRectSize();

	globalRect.SetPosition(position);
	globalRect.SetSize(size);

	renderer->DrawRect(&globalRect, &color);
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
