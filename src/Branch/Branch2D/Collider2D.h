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
	class Collider2D : public Branch2D
	{

		// # Variables + Getters/Setters
	private:

	public:

		Rect2 Rect = Rect2();

		// ###

		// # Functions

	private:

		void _OnCollision(Collider2D* collider);

	public:

		PERCH_API Collider2D(Engine* engine);

		PERCH_API bool DoesCollideWith(Collider2D* collider);
		PERCH_API void GetAABB(float& left, float& top, float& right, float& bottom);

		PERCH_API virtual void OnCollision(Collider2D* collider);

		PERCH_API virtual void CollisionUpdate() override;

		PERCH_API virtual void PhysicsUpdate() override;

		PERCH_API virtual void Draw(SDL_Renderer* renderer) override;

		// ###

	};


}
