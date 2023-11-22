#include "Color.h"

using namespace std;
using namespace Perch;

Color::Color()
{}

Color::Color(Uint8 gray)
{
	R = G = B = gray;
}

Color::Color(Uint8 gray, Uint8 a)
{
	R = G = B = gray;
	A = a;
}

Color::Color(Uint8 r, Uint8 g, Uint8 b)
{
	R = r;
	G = g;
	B = b;
}

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

Color::operator SDL_Color() const
{
	return SDL_Color{R, G, B, A};
}

bool Color::operator==(Color const& other)
{
	return R == other.A && G == other.G && B == other.B && A == other.A;
}

bool Color::operator!=(Color const& other)
{
	return R != other.A || G != other.G || B != other.B || A != other.A;
}
