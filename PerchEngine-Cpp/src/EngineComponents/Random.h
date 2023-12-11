#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
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

		PERCH_API int RandomInt();
		// Exclusive of max
		PERCH_API int RandomInt(int max);
		// Inclusive of min, Exclusive of max
		PERCH_API int RandomInt(int min, int max);

		// Returns a value between 0.0f and 1.0f, Inclusive of both limits
		PERCH_API float RandomFloat();
		// Inclusive of max
		PERCH_API float RandomFloat(float max);
		// Inclusive of min and max
		PERCH_API float RandomFloat(float min, float max);


		// ###
	};
}
