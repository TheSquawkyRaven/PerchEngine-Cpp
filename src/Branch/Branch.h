#pragma once

#include "../Engine.h"

#include <SDL.h>

#include <string>
#include <vector>

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
		inline std::string GetName() { return Name; }

	private:

		Branch* Parent = NULL;
		std::vector<Branch*> Children;

		// ###


		// # Functions

	private:

		int GetChildIndex(Branch* child);
		
		void _Init();
		void _Ready();

		void _Update();
		void _Draw(SDL_Surface& MainSurface);
		void _Destroy(bool isChainedDestroy);

	public:

		virtual void Init();
		virtual void Ready();

		virtual void Update();
		virtual void Draw(SDL_Surface& MainSurface);

		virtual void Destroy();

		// ###

	};


}
