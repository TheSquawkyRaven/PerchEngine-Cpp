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
		Vector2 Position = {};
		Vector2 Scale = {};

		// ###


		// # Functions
		// ###

	protected:

		Branch2D();

	};


}
