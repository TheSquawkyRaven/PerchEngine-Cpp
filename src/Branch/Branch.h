#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


#include "../Engine.h"
#include "Script.h"

#include <SDL.h>

#include <string>
#include <vector>
#include <memory>

namespace Perch
{
	/// <summary>
	/// A Branch is a container that can hold data and other branches as children.
	/// This is similar to Godot's Node.
	/// </summary>
	class Branch
	{

		friend class Engine;

		// # Variables + Getters/Setters

	private:

		std::string name = "Branch";
		

	protected:

		Engine* engine = nullptr;
		std::unique_ptr<Script> script = nullptr;

	public:

		PERCH_API inline void SetName(std::string name) { this->name = name; }
		PERCH_API inline std::string GetName() const { return name; }

	private:

		Branch* parent = nullptr;
		std::vector<std::unique_ptr<Branch>> children;

		bool readyExecuted = false;
		bool updated = false;
		bool physicsUpdated = false;
		bool drawn = false;

	public:

		PERCH_API inline bool IsReady() const { return readyExecuted; }

		PERCH_API inline Branch* GetParent() { return parent; }

		// ###


		// # Functions

	private:

		int GetChildIndex(Branch* child);

		void _Ready();

		void _Update();
		void _UpdateOut();
		void _PhysicsUpdate();
		void _CollisionUpdate();
		void _Draw(SDL_Renderer* renderer);
		void _DrawOut(SDL_Renderer* renderer);
		void _Destroy(bool isChainedDestroy);

	public:

		PERCH_API Branch(Engine* engine);

		PERCH_API void AttachChild(std::unique_ptr<Branch> branch);

		PERCH_API void AttachScript(std::unique_ptr<Script> script);

		// Ready - Preorder, Called upon attaching to a branch of the main tree or when the tree is run. Only called once
		PERCH_API virtual void Ready();

		// Update - Preorder, Called every frame
		PERCH_API virtual void Update();
		// UpdateOut - Called every frame after Updating all children
		PERCH_API virtual void UpdateOut();

		// PhysicsUpdate - Preorder, Called every frame after update, before collision update
		PERCH_API virtual void PhysicsUpdate();
		// CollisionUpdate - Preorder, Called every frame after physics update, before draw
		PERCH_API virtual void CollisionUpdate();

		// Draw - Preorder, Called every frame. Update first, then draw
		PERCH_API virtual void Draw(SDL_Renderer* renderer);
		// DrawOut - Called every frame right after Drawing all children
		PERCH_API virtual void DrawOut(SDL_Renderer* renderer);

		PERCH_API void Destroy();

		// OnDestroy - POSTorder, Called while destroying. Uninitialize pointers here.
		PERCH_API virtual void OnDestroy();

		// ###

	};


}
