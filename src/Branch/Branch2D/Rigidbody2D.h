#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


#include "Branch2D.h"

#include "../../Structs/Vector2.h"
#include "../../Structs/Rect2.h"

#include <SDL.h>
#include <memory>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	// Children are drawn on this viewport
	class Rigidbody2D : public Branch2D
	{

		// # Variables + Getters/Setters
	private:

		Vector2 ApplyingForce;
		bool ForceApplied = true;

	public:

		// TODO move to global gravity and change this to local gravity scale
		float Gravity = 0.0f;

		// TODO implement Drag
		float Drag = 0.0f;

		Vector2 Velocity = 0.0f;

		// ###

		// # Functions

	private:

	public:

		PERCHENGINECPP_API void AddForce(Vector2 force);

		PERCHENGINECPP_API virtual void PhysicsUpdate() override;

		// ###

	};


}
