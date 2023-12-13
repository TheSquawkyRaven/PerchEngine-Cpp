

#include "Random.h"

#include "../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

Random::Random()
{
	srand(time(0));
}

int Random::RandomInt()
{
	return rand();
}

int Random::RandomInt(int max)
{
	return rand() % max;
}

int Random::RandomInt(int min, int max)
{
	return min + RandomInt(max - min);
}

float Random::RandomFloat()
{
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float Random::RandomFloat(float max)
{
	return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / max));
}

float Random::RandomFloat(float min, float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}
