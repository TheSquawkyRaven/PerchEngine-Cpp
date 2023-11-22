#pragma once

#include <SDL.h>

#include "Vector2i.h"

#include <memory>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	struct Vector2
	{

	public:
		float X = 0;
		float Y = 0;


	public:

		Vector2();
		Vector2(float x, float y);
		Vector2(float val);

		float Magnitude() const;

		float Dot(Vector2 const& other) const;
		float Distance(Vector2 const& other) const;

		void Normalize();
		Vector2 NormalizedVector() const;

		Vector2 Midpoint(Vector2 const& other) const;
		Vector2 ProportionalPoint(Vector2 const& other, float proportion) const;

		std::shared_ptr<SDL_Point> GetSDLPoint() const;

		operator Vector2i() const;

		Vector2 operator+(Vector2 const& other);
		Vector2 operator-(Vector2 const& other);
		Vector2 operator*(Vector2 const& other);
		Vector2 operator/(Vector2 const& other);

		Vector2 operator+(float const& other);
		Vector2 operator-(float const& other);
		Vector2 operator*(float const& other);
		Vector2 operator/(float const& other);

		bool operator==(Vector2 const& other);
		bool operator!=(Vector2 const& other);

	};

}
