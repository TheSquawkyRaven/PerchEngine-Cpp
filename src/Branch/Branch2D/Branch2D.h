#pragma once

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
		Vector2 Position = {};
		// TODO + Rotation
		// Scale - Local Scale (1, 1) is full size
		Vector2 Scale = Vector2(1, 1);

		// ###


		// # Functions
		// ###

	protected:

		Branch2D();

		Vector2 _GetGlobalPosition();
		Vector2 _GetGlobalScale();

	public:

		virtual Vector2 GetGlobalPosition();
		virtual Vector2 GetGlobalScale();

	};


}
