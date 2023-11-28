#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
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

		Vector2 applyingForce;
		bool forceApplied = true;

	public:

		// TODO move to global gravity and change this to local gravity scale
		float gravity = 0.0f;

		// TODO implement Drag
		float drag = 0.0f;

		Vector2 velocity = 0.0f;

		// ###

		// # Functions

	private:

	public:

		PERCH_API Rigidbody2D(Engine* engine) : Branch2D(engine) {};

		PERCH_API virtual void PhysicsUpdate() override;

		PERCH_API void AddForce(Vector2 force);

		// ###

	};


}
