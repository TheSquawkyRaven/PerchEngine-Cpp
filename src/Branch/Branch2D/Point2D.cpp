#include "pch.h"

#include "Point2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void Point2D::SetupDraw(Renderer* renderer)
{
	SetupDefaultDrawOrder(renderer);
}

void Point2D::Draw(Renderer* renderer)
{
	Vector2 point = GetGlobalPointPosition();

	renderer->DrawPoint(point.x, point.y, &color);
}

Vector2 Point2D::GetGlobalPointPosition()
{
	return GetGlobalPosition() + pointPosition;
}
