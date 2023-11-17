#include "Vector2i.h"

using namespace Perch;

Perch::Vector2i::Vector2i()
{
}

Perch::Vector2i::Vector2i(int x, int y)
{
	X = x;
	Y = y;
}

Perch::Vector2i::Vector2i(int val)
{
	X = Y = val;
}
