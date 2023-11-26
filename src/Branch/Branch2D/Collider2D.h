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

		PERCHENGINECPP_API Collider2D(Engine* engine);

		PERCHENGINECPP_API bool DoesCollideWith(Collider2D* collider);
		PERCHENGINECPP_API void GetAABB(float& left, float& top, float& right, float& bottom);

		PERCHENGINECPP_API virtual void OnCollision(Collider2D* collider);

		PERCHENGINECPP_API virtual void CollisionUpdate() override;

		PERCHENGINECPP_API virtual void PhysicsUpdate() override;

		PERCHENGINECPP_API virtual void Draw(SDL_Renderer* renderer) override;

		// ###

	};


}
