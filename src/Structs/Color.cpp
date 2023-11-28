#include "pch.h"

#include "Color.h"

using namespace std;
using namespace Perch;

Color::Color()
{}

Color::Color(Uint8 gray)
{
	r = g = b = gray;
}

Color::Color(Uint8 gray, Uint8 a)
{
	r = g = b = gray;
	this->a = a;
}

Color::Color(Uint8 r, Uint8 g, Uint8 b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::operator SDL_Color() const
{
	return SDL_Color{r, g, b, a};
}

bool Color::operator==(Color const& other)
{
	return r == other.a && g == other.g && b == other.b && a == other.a;
}

bool Color::operator!=(Color const& other)
{
	return r != other.a || g != other.g || b != other.b || a != other.a;
}
