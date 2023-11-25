#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
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
		float X = 0;
		float Y = 0;


	public:

		PERCHENGINECPP_API Vector2();
		PERCHENGINECPP_API Vector2(float x, float y);
		PERCHENGINECPP_API Vector2(float val);

		PERCHENGINECPP_API float Magnitude() const;

		PERCHENGINECPP_API float Dot(Vector2 const& other) const;
		PERCHENGINECPP_API float Distance(Vector2 const& other) const;

		PERCHENGINECPP_API void Normalize();
		PERCHENGINECPP_API Vector2 NormalizedVector() const;

		PERCHENGINECPP_API Vector2 Midpoint(Vector2 const& other) const;
		PERCHENGINECPP_API Vector2 ProportionalPoint(Vector2 const& other, float proportion) const;

		PERCHENGINECPP_API std::shared_ptr<SDL_Point> GetSDLPoint() const;

		PERCHENGINECPP_API operator Vector2i() const;

		PERCHENGINECPP_API Vector2 operator+(Vector2 const& other);
		PERCHENGINECPP_API Vector2 operator-(Vector2 const& other);
		PERCHENGINECPP_API Vector2 operator*(Vector2 const& other);
		PERCHENGINECPP_API Vector2 operator/(Vector2 const& other);

		PERCHENGINECPP_API Vector2 operator+(float const& other);
		PERCHENGINECPP_API Vector2 operator-(float const& other);
		PERCHENGINECPP_API Vector2 operator*(float const& other);
		PERCHENGINECPP_API Vector2 operator/(float const& other);

		PERCHENGINECPP_API bool operator==(Vector2 const& other);
		PERCHENGINECPP_API bool operator!=(Vector2 const& other);

	};

}
