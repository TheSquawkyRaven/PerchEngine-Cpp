#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


#include "../Branch.h"
#include "../../Structs/Vector2.h"

#include <SDL.h>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	class Branch2D : public Branch
	{

		// # Variables + Getters/Setters

	public:

		// Position - Local Position
		Vector2 Position = Vector2();
		// TODO + Rotation
		// Scale - Local Scale (1, 1) is full size
		Vector2 Scale = Vector2(1, 1);

		// ###


		// # Functions
		// ###

	protected:

		PERCHENGINECPP_API Vector2 _GetGlobalPosition();
		PERCHENGINECPP_API Vector2 _GetGlobalScale();

	public:

		PERCHENGINECPP_API Branch2D(Engine* engine) : Branch(engine) {};

		PERCHENGINECPP_API virtual Vector2 GetGlobalPosition();
		PERCHENGINECPP_API virtual Vector2 GetGlobalScale();

	};


}
