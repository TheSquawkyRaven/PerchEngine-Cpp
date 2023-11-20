#pragma once

#include "../Engine.h"

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

		friend class Perch::Engine;

		// # Variables + Getters/Setters

	private:

		std::string Name = "Branch";

	public:

		void SetName(std::string name);
		inline std::string GetName() const { return Name; }

	private:

		std::shared_ptr<Branch> Parent = NULL;
		std::vector<std::shared_ptr<Branch>> Children;

		std::stack<std::shared_ptr<Branch>> OutStack;

		bool ReadyCalled = false;

	protected:

		inline std::shared_ptr<Branch> GetParent() { return Parent; }

	public:

		inline bool IsReady() const { return ReadyCalled; }

		// ###


		// # Functions

	private:

		int GetChildIndex(Branch* child);
		
		void _Init(Engine* engine);
		void _Ready(Engine* engine);

		void _Update(Engine* engine);
		void _UpdateOut(Engine* engine);
		void _Draw(Engine* engine, SDL_Renderer* renderer);
		void _DrawOut(Engine* engine, SDL_Renderer* renderer);
		void _Destroy(Engine* engine, bool isChainedDestroy);

	protected:

		Branch();

	public:

		void AttachChild(std::shared_ptr<Branch> branch);

		// Init - Called right after constructor is ran, from Engine::CreateBranch
		// Will NOT call Init on children
		virtual void Init(Engine* engine);

		// Ready - Preorder, Called upon attaching to a branch of the main tree or when the tree is run. Only called once
		virtual void Ready(Engine* engine);

		// Update - Preorder, Called every frame
		virtual void Update(Engine* engine);
		// UpdateOut - Reverse Preorder, Called every frame after Update
		virtual void UpdateOut(Engine* engine);

		// Draw - Preorder, Called every frame. Update first, then draw
		virtual void Draw(Engine* engine, SDL_Renderer* renderer);
		// DrawOut - Reverse Preorder, Called every frame. Calls after draw
		virtual void DrawOut(Engine* engine, SDL_Renderer* renderer);

		void Destroy(Engine* engine);

		// OnDestroy - POSTorder, Called while destroying. Uninitialize pointers here.
		virtual void OnDestroy(Engine* engine);

		// ###

	};


}
