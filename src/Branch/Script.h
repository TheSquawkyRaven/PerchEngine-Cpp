#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


// Main SDL Window
#include <SDL.h>

#include "../Engine.h"

#include <memory>

namespace Perch
{

	// For bool return functions, true represents success
	class Script
	{

		// # Variables + Getters/Setters

	private:

		Branch* attachedToBranch = nullptr;

	protected:

		Engine* engine = nullptr;

	public:

		inline void SetAttachedToBranch(Branch* branch) { attachedToBranch = branch; }
		PERCH_API inline Branch* GetAttachedToBranch() { return attachedToBranch; }

		// ###


		// # Functions

	private:


	public:

		PERCH_API Script(Engine* engine);

		// Init - Called right after constructor is ran, from Engine::CreateScript
		PERCH_API virtual void Init();

		// Ready - Preorder, Called upon attaching to a branch of the main tree or when the tree is run. Only called once
		PERCH_API virtual void Ready();

		// Update - Preorder, Called every frame
		PERCH_API virtual void Update();

		// Update - Preorder, Called every frame after update, before draw
		PERCH_API virtual void PhysicsUpdate();

		// Draw - Preorder, Called every frame. Update first, then draw
		PERCH_API virtual void Draw(Renderer* renderer);

		// OnDestroy - POSTorder, Called while destroying. Uninitialize pointers here.
		PERCH_API virtual void OnDestroy();

		// OnCollision2D - Called when it receives a collision2D event
		PERCH_API virtual void OnCollision2D(Collider2D* collider, CollisionState collisionState);
		
		// ###
	};
}
