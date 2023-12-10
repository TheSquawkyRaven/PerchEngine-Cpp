#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


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
		float x = 0;
		float y = 0;


	public:

		PERCH_API Vector2();
		PERCH_API Vector2(float x, float y);
		PERCH_API Vector2(float val);

		PERCH_API float Magnitude() const;

		PERCH_API float Dot(Vector2 const& other) const;
		PERCH_API float Distance(Vector2 const& other) const;

		PERCH_API void Normalize();
		PERCH_API Vector2 NormalizedVector() const;

		PERCH_API Vector2 Midpoint(Vector2 const& other) const;
		PERCH_API Vector2 ProportionalPoint(Vector2 const& other, float proportion) const;

		PERCH_API std::shared_ptr<SDL_Point> GetSDLPoint() const;

		PERCH_API operator Vector2i() const;

		// TODO +=, -=, *=, /=
		PERCH_API Vector2 operator+(Vector2 const& other);
		PERCH_API Vector2& operator+=(Vector2 const& other);
		PERCH_API Vector2 operator-(Vector2 const& other);
		PERCH_API Vector2& operator-=(Vector2 const& other);
		PERCH_API Vector2 operator*(Vector2 const& other);
		PERCH_API Vector2& operator*=(Vector2 const& other);
		PERCH_API Vector2 operator/(Vector2 const& other);
		PERCH_API Vector2& operator/=(Vector2 const& other);

		PERCH_API Vector2 operator+(float const& other);
		PERCH_API Vector2& operator+=(float const& other);
		PERCH_API Vector2 operator-(float const& other);
		PERCH_API Vector2& operator-=(float const& other);
		PERCH_API Vector2 operator*(float const& other);
		PERCH_API Vector2& operator*=(float const& other);
		PERCH_API Vector2 operator/(float const& other);
		PERCH_API Vector2& operator/=(float const& other);

		PERCH_API bool operator==(Vector2 const& other);
		PERCH_API bool operator!=(Vector2 const& other);

	};

}
