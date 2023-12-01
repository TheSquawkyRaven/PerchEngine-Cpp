#include "pch.h"

#include "Line2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void Line2D::Draw(Renderer* renderer)
{
	Vector2 start = GetGlobalStartPosition();
	Vector2 end = GetGlobalEndPosition();

	renderer->DrawLine(start.x, start.y, end.x, end.y, &color);
}

Vector2 Line2D::GetGlobalStartPosition()
{
	return GetGlobalPosition() + startPosition;
}

Vector2 Line2D::GetGlobalEndPosition()
{
	return GetGlobalPosition() + endPosition;
}
