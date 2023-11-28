#include "pch.h"

#include "Vector2i.h"
#include "Vector2.h"

using namespace Perch;

Vector2i::operator Vector2() const
{
	return Vector2(x, y);
}

Vector2i::Vector2i()
{
}

Vector2i::Vector2i(int x, int y)
{
	this->x = x;
	this->y = y;
}

Vector2i::Vector2i(int val)
{
	x = y = val;
}
