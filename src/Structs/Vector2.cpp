#include "Vector2.h"

using namespace Perch;

Perch::Vector2::Vector2()
{
}

Perch::Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
}

Perch::Vector2::Vector2(float val)
{
	X = Y = val;
}
