#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


// Main SDL Window
#include <SDL.h>

#include <stdlib.h>
#include <ctime>

namespace Perch
{

	class Random
	{

		// # Variables + Getters/Setters

	private:

	public:

		// ###


		// # Functions

	private:

	public:

		Random();

		PERCHENGINECPP_API int RandomInt();
		// Exclusive of max
		PERCHENGINECPP_API int RandomInt(int max);
		// Inclusive of min, Exclusive of max
		PERCHENGINECPP_API int RandomInt(int min, int max);

		// Returns a value between 0.0f and 1.0f, Inclusive of both limits
		PERCHENGINECPP_API float RandomFloat();
		// Inclusive of max
		PERCHENGINECPP_API float RandomFloat(float max);
		// Inclusive of min and max
		PERCHENGINECPP_API float RandomFloat(float min, float max);


		// ###
	};
}
