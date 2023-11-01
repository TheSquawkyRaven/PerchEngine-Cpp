#pragma once

#include "Engine.h"

#include <SDL.h>

#include <string>
#include <vector>

namespace Perch
{
	/// <summary>
	/// A Branch is a container that can hold data and other branches as children.
	/// This is similar to Godot's Node.
	/// </summary>
	class Engine::Branch
	{

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

		void Destroy(bool isChainedDestroy);

	public:

		void Destroy();

		// ###

	};


}
