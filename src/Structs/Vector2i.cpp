#include "Vector2i.h"
#include "Vector2.h"

using namespace Perch;

Vector2i::operator Vector2() const
{
	return Vector2(X, Y);
}

Vector2i::Vector2i()
{
}

Vector2i::Vector2i(int x, int y)
{
	X = x;
	Y = y;
}

Vector2i::Vector2i(int val)
{
	X = Y = val;
}
