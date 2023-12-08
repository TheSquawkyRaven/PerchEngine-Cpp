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
#include <unordered_set>

namespace Perch
{

	enum class CollisionState
	{
		Enter,
		Stay,
		Exit
	};

	/// <summary>
	/// 
	/// </summary>
	// 
	class Collider2D : public Branch2D
	{
	public:

		// # Variables + Getters/Setters
	private:

		std::unordered_set<Collider2D*> collidersInContact;

	public:

		Rect2 rect = Rect2();

		// ###

		// # Functions

	private:

		void _OnCollision(Collider2D* collider, CollisionState collisionState);

	public:

		PERCH_API Collider2D(Engine* engine) : Branch2D(engine) {}

		PERCH_API virtual void CollisionUpdate() override;
		PERCH_API virtual void PhysicsUpdate() override;
		PERCH_API virtual void SetupDraw(Renderer* renderer) override;
		PERCH_API virtual void Draw(Renderer* renderer) override;

		PERCH_API virtual void OnCollision(Collider2D* collider, CollisionState collisionState);

		//PERCH_API virtual void AddToCollision(Collider2D* collider);

		PERCH_API bool DoesCollideWith(Collider2D* collider);
		PERCH_API void GetAABB(float& left, float& top, float& right, float& bottom);

		// ###

	};


}
