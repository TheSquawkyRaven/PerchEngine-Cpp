#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


#include "../Branch.h"
#include "../../Structs/Vector2.h"

#include <SDL.h>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	class BranchUI : public Branch
	{

		// # Variables + Getters/Setters

	public:

		// TODO advanced UI control, anchors, pivots etc
		// Position - Local Position
		Vector2 position = Vector2();
		// TODO + Rotation
		// Scale - Local Scale (1, 1) is full size
		Vector2 scale = Vector2(1, 1);

		// ###


		// # Functions
		// ###

	public:

		PERCH_API BranchUI(Engine* engine) : Branch(engine) {};

		PERCH_API virtual Vector2 GetGlobalPosition();
		PERCH_API virtual Vector2 GetGlobalScale();



	};


}
