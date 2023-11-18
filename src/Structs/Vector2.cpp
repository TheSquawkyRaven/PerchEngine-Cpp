#include "Vector2.h"
#include <cmath>

using namespace std;
using namespace Perch;

Vector2::Vector2()
{
}

Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
}

Vector2::Vector2(float val)
{
	X = Y = val;
}

float Vector2::Magnitude() const
{
	return sqrtf(X * X + Y * Y);
}

float Vector2::Dot(Vector2 const& other) const
{
	return X * other.X + Y * other.Y;
}

float Vector2::Distance(Vector2 const& other) const
{
	Vector2 current = *this;
	return (current - other).Magnitude();
}

void Vector2::Normalize()
{
	float magnitude = Magnitude();
	X /= magnitude;
	Y /= magnitude;
}

Vector2 Vector2::NormalizedVector() const
{
	Vector2 current = *this;
	current.Normalize();
	return current;
}

Vector2 Vector2::Midpoint(Vector2 const& other) const
{
	return ProportionalPoint(other, 0.5f);
}

Vector2 Vector2::ProportionalPoint(Vector2 const& other, float proportion) const
{
	return Vector2((X + other.X) * proportion, (Y + other.Y) * proportion);
}





Vector2 Vector2::operator+(Vector2 const& other)
{
	return Vector2(X + other.X, Y + other.Y);
}

Vector2 Vector2::operator-(Vector2 const& other)
{
	return Vector2(X - other.X, Y - other.Y);
}

Vector2 Vector2::operator*(Vector2 const& other)
{
	return Vector2(X * other.X, Y * other.Y);
}

Vector2 Vector2::operator/(Vector2 const& other)
{
	return Vector2(X / other.X, Y / other.Y);
}

Vector2 Vector2::operator+(float const& other)
{
	return Vector2(X + other, Y + other);
}

Vector2 Vector2::operator-(float const& other)
{
	return Vector2(X - other, Y - other);
}

Vector2 Vector2::operator*(float const& other)
{
	return Vector2(X * other, Y * other);
}

Vector2 Vector2::operator/(float const& other)
{
	return Vector2(X / other, Y / other);
}

bool Vector2::operator==(Vector2 const& other)
{
	return X == other.X && Y == other.Y;
}

bool Vector2::operator!=(Vector2 const& other)
{
	return X != other.X && Y != other.Y;
}
